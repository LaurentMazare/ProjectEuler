(* Run with: ocamlopt.opt bigarray.cmxa e012.ml -o e012 && time ./e012 *)
(* prime_decomposition n returns a function f such that f x for x < n returns
 * a list [p1,q1; p2,q2; ...; pn,qn] if x = p1^q1 * p2^q2 * ... * pn^qn *)
let prime_decomposition n =
  (* Some imperative code for the Erastostene sieve :( *)
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

let pd = prime_decomposition 100_000_000
let nb_divs n =
  List.fold_left (fun acc (_, q) -> (q+1)*acc) 1 (pd n)
let first pred =
  let rec aux n = if pred n then n else aux (n+1) in
  aux 2

let () =
  let i = first (fun n -> 500 <= nb_divs ((n*(n+1))/2)) in
  Format.printf "%d\n" ((i*(i+1))/2)
