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

let sum_seq f a b =
  let rec aux acc a = if a > b then acc else aux (f a + acc) (a+1) in
  aux 0 a

let pd = prime_decomposition 10_000_000
let rec last = function
  | [] -> failwith "Empty list"
  | [p] -> p
  | _::q -> last q
let f x =
  let pd = pd x in
  if List.length pd == 1 then 1
  else
    let p, _ = last pd in
    let rec aux c =
      if ((c+1) * (c+1)) mod x = c+1 then c+1
      else if (c*c) mod x = c then c
      else aux (c - p)
    in
    aux (x-p)
;;
Format.printf "%d" (sum_seq f 2 10_000_000)

