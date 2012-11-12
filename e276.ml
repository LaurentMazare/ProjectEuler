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

let array_initf f init nb =
  let res = Bigarray.Array1.create Bigarray.int64 Bigarray.c_layout nb in
  Bigarray.Array1.set res 0 init;
  for i = 1 to nb - 1 do
    Bigarray.Array1.set res i (f (Bigarray.Array1.get res (i-1)) i)
  done;
  res

let loop_sum low up f =
  let rec aux acc low = if low > up then acc else aux (Int64.add acc (f low)) (low + 1) in
  aux 0L low

let () =
  (* Use Int64 because of precision issue, 2**62 is not enough, 2**63 is... *)
  let lim = 10_000_000 in
  let o = Int64.of_int in
  let init prev =
    let ( + ), ( * ), ( / ) = Int64.add, Int64.mul, Int64.div in
    fun i -> prev + if i mod 2 = 0 then (o i*o i+24L)/48L else ((o i+3L)*(o i+3L)+24L)/48L
  in
  let nb_tri = array_initf init 0L (lim+1) in
  let pd = prime_decomposition (lim/2) in
  let count n =
    let sign = List.fold_left (fun acc (_, q) -> if q = 1 then -acc else 0) 1 (pd n) in
    Int64.mul (o sign) (Bigarray.Array1.get nb_tri (lim / n))
  in
  Format.printf "%s\n" (Int64.to_string (loop_sum 1 (lim/3) count))
