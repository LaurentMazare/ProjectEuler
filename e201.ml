(* Uses BigArray of char for memory efficiency, 'o': one, 'z': zero, 'm': more. *)
let add x y = match x, y with | 'z', x | x, 'z' -> x | _, _ -> 'm'
let array_init n f =
  let res = Bigarray.Array1.create Bigarray.char Bigarray.c_layout n in
  for i = 0 to n-1 do Bigarray.Array1.set res i (f i) done;
  res
let array_length a = Bigarray.Array1.dim a
let array_get a i =
  if 0 <= i && i < array_length a then Bigarray.Array1.get a i else 'z'

let () =
  let cache = Hashtbl.create 4 in
  let rec reachable n = function
    | [] -> array_init 0 (fun _ -> 'z')
    | p::q as l ->
        if Hashtbl.mem cache (l, n) then Hashtbl.find cache (l, n)
        else
          let m = List.fold_left max 0 l in
          if n = 1 then array_init (m+1) (fun i -> if List.mem i l then 'o' else 'z')
          else
            let r1 = reachable (n-1) q in
            let r2 = reachable n q in
            let l1, l2 = array_length r1, array_length r2 in
            let init i = add (array_get r2 i) (array_get r1 (i-p)) in
            let res = array_init (max (l1+p) l2) init in
            Hashtbl.add cache (l, n) res;
            res
  in
  let r = reachable 50 (Array.to_list (Array.init 100 (fun i -> (i+1)*(i+1)))) in
  let sum = ref 0 in
  for i = 0 to array_length r do if array_get r i == 'o' then sum := !sum + i done;
  Format.printf "%d\n" !sum
;;
