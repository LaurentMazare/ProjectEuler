(* Compute self-avoiding walks of given size *)
let walks size =
  let rec aux_walks acc size path =
    if size = 0 then path::acc
    else
      let x, y = List.hd path in
      List.fold_left
      (fun acc (dir_x, dir_y) ->
        let tmp_x = x + dir_x in
        let tmp_y = y + dir_y in
        let elem = tmp_x, tmp_y in
        if List.mem elem path then acc
        else
          aux_walks acc (size-1) (elem::path)
      )
      acc
      [-1, 0; 1, 0; 0, -1; 0, 1]
  in
  aux_walks [] (size-2) [0, 0; 0, 1]

(* Make element of a sorted list unique *)
let uniq l =
  let rec aux acc = function
    | [] -> acc
    | p::(q::r as l) when p = q -> aux acc l
    | p::q -> aux (p::acc) q
  in
  aux [] l

(* Extract a list of neighbor information, i.e. a list of
   array a such that a[i+nb*j] is true iff the ith elt of
   the walk is a neighbor of the jth elt of the walk. *)
let links_of_walks nb walks =
  let rec aux acc i = function
    | [] -> acc
    | (x, y)::q ->
        let rec aux_bis acc j = function
          | [] -> acc
          | (x', y')::q when (x'=x && abs(y-y')=1) || (y'=y && abs(x-x')=1) ->
              aux_bis ((i, j)::acc) (j+1) q
          | _::q -> aux_bis acc (j+1) q
        in
        aux (aux_bis acc (i+1) q) (i+1) q
  in
  let array_of_link l =
    let res = Array.make (nb*nb) false in
    List.iter (fun (i, j) -> Array.set res (nb*i + j) true) l;
    res
  in
  let l = uniq (List.sort compare (List.rev_map (aux [] 0) walks)) in
  List.rev_map array_of_link l

(* Basis 2 decomposition: 2**i+2**j+2**k -> [i,j,k] *)
let rec list_of_int acc i = function
  | 0 -> acc
  | n when n mod 2 = 1 -> list_of_int (i::acc) (i+1) (n/2)
  | n -> list_of_int acc (i+1) (n/2)

(* Generate all pairs *)
let rec pairs acc = function
  | [] -> acc
  | i::q ->
    let rec aux acc = function
      | [] -> acc
      | j::q' -> aux ((i, j)::acc) q'
    in
    pairs (aux acc q) q

let run nb =
  let walks = walks nb in
  Printf.printf "Walks: %d\n" (List.length walks);
  let links = links_of_walks nb walks in
  Printf.printf "Links: %d\n" (List.length links);
  let rec sum_hh acc n =
    if n = 0 then acc
    else
      let n = n - 1 in
      let list = list_of_int [] 0 n in
      let pairs = pairs [] list in
      let nb_hh l =
        List.fold_left
        (fun acc (j, i) -> acc + if Array.get l (nb*i + j) then 1 else 0)
        0
        pairs
      in
      let nb = List.fold_left (fun acc l -> max acc (nb_hh l)) 0 links in
      sum_hh (acc+nb) n
  in
  let nb_hh = sum_hh 0 (1 lsl nb) in
  let e = float_of_int nb_hh /. (2.0 ** float_of_int nb) in
  Printf.printf "Nb: %d E: %.14f\n" nb_hh e;
  ()

let _ = run 15
