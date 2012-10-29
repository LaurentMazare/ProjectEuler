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

(* This generates all the factors from a prime decomposition. *)
let all_factors lim factors =
  let rec aux acc = function
    | [] -> if acc <= lim then [acc] else []
    | (p1, q1)::q ->
        let rec aux_bis acc_l p exponent =
          if exponent > q1 then acc_l
          else
            let acc_l = List.append (aux (p*acc) q) acc_l in
            aux_bis acc_l (p * p1) (exponent + 1)
        in
        aux_bis [] 1 0
  in
  aux 1 factors

(* a^2 + b^2 = c^2 + 1 is equivalent to (a-1)*(a+1) = (c+b)*(c-b)
 * For all possible values of a, generate the prime decomposition
 * for (a-1) * (a+1) hence all its possible factors f. Then c+b = f
 * and c-b = (a-1)*(a+1)/f. Note that a <= (a+b+c)/(2+sqrt(2))*)
let () =
  let lim = 25_000_000 in
  let prime_d = prime_decomposition (5+lim/3) in
  Format.printf "Sieving done!\n";
  let rec nb_triples acc a =
    if a > (lim * 100) / 341 then acc (* 2+sqrt(2) ~ 3.414 *)
    else
      let prime_d = merge_d (prime_d (a+1)) (prime_d (a-1)) in
      let product = (a+1) * (a-1) in (* This only works on a 64 bit architecture *)
      let factors = all_factors lim prime_d in
      let check_bc cplusb =
        let cminusb = product / cplusb in
        let c = (cplusb + cminusb) / 2 in
        let b = (cplusb - cminusb) / 2 in
        a <= b && b <= c && a + b + c <= lim && cplusb mod 2 = cminusb mod 2
      in
      let acc = List.fold_left (fun acc bc -> acc + if check_bc bc then 1 else 0) acc factors in
      nb_triples acc (a+1)
  in
  Format.printf "%d\n" (nb_triples ((lim-1)/2) 2);;
