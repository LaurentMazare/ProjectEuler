(* Triples have the form a = 3*alpha + 2,
 * (alpha+1)^2 * (8*alpha+5) = b^2 * c
 * with a + b + c <= 100.10^6             *)

(* Some imperative code for the Erastostene sieve :( *)
let prime_decomposition n =
  let factors = Bigarray.Array1.create Bigarray.int Bigarray.c_layout (n+1) in
  for i = 2 to n do
    if Bigarray.Array1.get factors i = 0 then
      let rec aux j =
        if j <= n then (
          Bigarray.Array1.set factors j i;
          aux (j+i)
        )
      in
      aux i
  done;
  let rec aux acc k =
    if k < 2 || k > n then acc
    else
      let f = Bigarray.Array1.get factors k in
      let rec nb_of_f acc k =
        if k mod f = 0 then nb_of_f (acc+1) (k/f)
        else acc, k
      in
      let nb_f, rest = nb_of_f 0 k in
      aux ((f, nb_f)::acc) rest
  in
  fun k -> List.sort compare (aux [] k)

(* Merge two (int, int) associative lists by summing equal elements.
 * Assume that the inputs are sorted, example:
 * [1, 2; 3, 5; 5, 7], [2, 1; 3, 2] -> [1, 2; 2, 1; 3, 7; 5, 7] *) 
let rec merge_d l1 l2 = (* l1 and l2 are ordered *)
  match l1, l2 with
  | [], l
  | l, [] -> l
  | (p1, a1)::q1, (p2, a2)::q2 when p1 = p2 -> (p1, a1+a2)::(merge_d q1 q2)
  | (p1, a1)::q1, (p2, _)::_ when p1 < p2 -> (p1, a1)::(merge_d q1 l2)
  | l1, (p2, a2)::q2 -> (p2, a2)::(merge_d l1 q2)

(* Very unoptimized function that extracts all square f out of a factor list
 * as a double. *)
let sq_factors_of_factors lim factors =
  let rec aux acc = function
    | [] -> if acc <= lim then [acc] else []
    | (p1, q1)::q ->
        let p1_2 = float_of_int p1 *. float_of_int p1 in
        let rec aux_bis acc_l p exponent =
          if exponent > q1 then acc_l
          else
            let acc_l = List.append (aux (p*.acc) q) acc_l in
            aux_bis acc_l (p *. p1_2) (exponent + 2)
        in
        aux_bis [] 1.0 0
  in
  aux 1.0 factors

let () =
  let lim = 110000000 in
  let float_lim = float_of_int lim +. 0.5 in
  let float_lim2 = float_lim *. float_lim in
  let prime_d = prime_decomposition 300000000 in
  let rec nb_of_triples acc alpha =
    if 3*alpha+2 >= lim then acc
    else
      let factors = prime_d (alpha+1) in
      let factors = merge_d factors factors in
      let factors = merge_d factors (prime_d (8*alpha + 5)) in
      let sq_factors = sq_factors_of_factors float_lim2 factors in
      let check b2 =
        let alpha = float_of_int alpha in
        let b = sqrt b2 in
        let a = 3.0 *. alpha +. 2.0 in
        let c = (alpha +. 1.) *. (alpha +. 1.) *. (8. *. alpha +. 5.) /. b2 in
        if a +. b +. c <= float_lim then 1 else 0
      in
      let tmp = List.fold_left (fun acc b2 -> acc + check b2) 0 sq_factors in
      nb_of_triples (tmp + acc) (alpha+1)
  in
  Format.printf "%d\n" (nb_of_triples 0 0);;
