(* This only works on a 64 bits ocaml.
 * The idea is to compute for every c all the pairs a and b such that
 * x^2 + y^2 = (r-z)(r+z) by reusing the square decomposition function
 * from Project Euler #224.
 * Also note that it x^2 + y^2 + z^2 = 2r' implies that 2 divides x,
 * y and z so it is sufficient to solve for r = 5^10.
 * Run it with: ocamlopt.opt bigarray.cmxa e360.ml -o e360 && time ./e360
 *)
open Dioph

module PS = Set.Make( 
  struct
    let compare = Pervasives.compare
    type t = int * int
  end )

let radius = pow 5 10
let pd = prime_decomposition (2 + 2*radius)
let rec assoc_add = function (* Requires the associative lists to be sorted. *)
  | [], l | l, [] -> l
  | (a1, b1)::q1, (a2, b2)::q2 when a1 = a2 -> (a1, b1+b2)::assoc_add (q1, q2)
  | (a1, b1)::q1, ((a2, _)::q2 as l2) when a1 < a2 -> (a1, b1)::assoc_add (q1, l2)
  | l1, p2::q2 -> p2::assoc_add (l1, q2)

let dist x y z =
  let two_p a = if a != 0 then 2 else 1 in
  (x + y + z) * two_p x * two_p y * two_p z * two_p (x - y)

let solutions_for_z z =
  let factors1, factors2 = pd (radius-z), pd (radius+z) in
  let decomposition = assoc_add (factors1, factors2) in
  let pairs =
    if radius = z then PS.singleton (0, 0)
    else
      let ts = two_squares decomposition in
      let ts = List.fold_left (fun acc x -> PS.add x acc) PS.empty ts in
      if List.for_all (fun (_, q) -> q mod 2 == 0) decomposition then
        PS.add (0, List.fold_left (fun acc (p, q) -> acc * pow p (q/2)) 1 decomposition) ts
      else ts
  in
  PS.fold (fun (x, y) acc -> acc + dist x y z) pairs 0

let sum_seq f a b =
  let rec aux acc a = if a > b then acc else aux (f a + acc) (a+1) in
  aux 0 a

let () = Format.printf "Total: %d\n" (pow 2 10 * sum_seq solutions_for_z 0 radius)
