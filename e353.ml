(* This only works on a 64 bits ocaml.
 * The idea is to compute for every c all the pairs a and b such that
 * x^2 + y^2 = (r-z)(r+z) by reusing the square decomposition function
 * from Project Euler #224.
     1 0.5000000000
     3 0.2360456664
     7 0.1784943998
    15 0.1071479480
    31 0.0874453003
    63 0.0415156841
   127 0.0492283919
   255 0.0267478544
   511 0.0183816796
  1023 0.0113610997
  2047 0.0115524939
  4095 0.0053033044
  8191 0.0058226833
 16383 0.0030517644
 32767 0.0024188104
 *)
let rec pow x n =
  if n = 0 then 1
  else if n mod 2 = 0 then let x = pow x (n/2) in x * x
  else x * pow x (n-1)

let rec pow_mod x n p =
  if n = 0 then 1
  else if n mod 2 = 0 then
    let x = pow_mod x (n/2) p in (x * x) mod p
  else (x * pow_mod x (n-1) p) mod p

let sqrt_m1 p = (* Square root of -1 mod p, Tonelli-Shanks would be better. *)
  let pp = (p - 1) / 4 in
  let rec iter a =
    let x = pow_mod a pp p in
    if pow_mod x 2 p = p - 1 then x else iter (a+1)
  in
  iter 2

let two_squares_1 n = (* Brillhart algorithm, 1972 *)
  let rec gcd a b =
    if a * a < n then (a, b mod a) else gcd b (a mod b)
  in
  gcd n (sqrt_m1 n)

module PS = Set.Make( 
  struct
    let compare = Pervasives.compare
    type t = int * int
  end )

let two_squares_ factors1 = (* Two squares decomposition for a product of primes 4k+1 or 2. *)
  let pairs = List.map (fun x -> if x = 2 then (1, 1) else two_squares_1 x) factors1 in
  let aux acc (a, b) =
    if PS.is_empty acc then PS.singleton (a, b)
    else
      let add_comp (c, d) acc =
        PS.add (a*c+b*d, abs (a*d-b*c)) (PS.add (a*d+b*c, abs (a*c-b*d)) acc)
      in
      PS.fold add_comp acc PS.empty
  in
  List.fold_left aux PS.empty pairs

let expand_assoc l =
  let rec aux acc = function
    | [] -> acc
    | (a, 0)::q -> aux acc q
    | (a, n)::q -> aux (a::acc) ((a, n-1)::q)
  in
  aux [] l

(* Takes as input the prime decomposition for n as an assoc list and returns
 * a set of all the pairs (a, b) such that n = a^2 + b^2. *)
let two_squares factors =
  let fact3 = List.filter (fun (x, _) -> x mod 4 = 3) factors in
  let fact1 = List.filter (fun (x, _) -> x mod 4 = 1) factors in
  let fact2 = List.filter (fun (x, _) -> x = 2) factors in
  let fact1 = expand_assoc fact1 in
  if List.exists (fun (_, q) -> q mod 2 = 1) fact3 then PS.empty
  else
    let mult, fact1 =
      match fact2 with
      | [p, q] when q mod 2 = 1 -> (pow 2 (q/2)), 2::fact1
      | [p, q] when q mod 2 = 0 -> (pow 2 (q/2)), fact1
      | _ -> 1, fact1
    in
    let pairs = two_squares_ fact1 in
    let mult = mult * List.fold_left (fun acc (p, q) -> acc * pow p (q/2)) 1 fact3 in
    PS.fold (fun (x, y) acc -> PS.add (mult * min x y, mult * max x y) acc) pairs PS.empty

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

let radius n = pow 2 n - 1
let max_radius = radius 15
let pd = prime_decomposition (2 + 2*max_radius)
let rec assoc_add = function (* Requires the associative lists to be sorted. *)
  | [], l | l, [] -> l
  | (a1, b1)::q1, (a2, b2)::q2 when a1 = a2 -> (a1, b1+b2)::assoc_add (q1, q2)
  | (a1, b1)::q1, ((a2, _)::q2 as l2) when a1 < a2 -> (a1, b1)::assoc_add (q1, l2)
  | l1, p2::q2 -> p2::assoc_add (l1, q2)

let sqr_f x = x *. x
let pi = 4. *. atan 1.
let crisk radius (x, y, z) (x', y', z') =
  let float f = float_of_int f /. float_of_int radius in
  let x, y, z = float x, float y, float z in
  let x', y', z' = float x', float y', float z' in
  let d2 = sqr_f (x'-.x) +. sqr_f (y'-.y) +. sqr_f (z'-.z) in
  let theta = acos (1. -. d2 /. 2.) in
  sqr_f (theta /. pi)

let pp (x, y, z) = Format.printf "%d %d %d\n" x y z

let solutions_for_z radius z =
  let factors1, factors2 = pd (radius-z), pd (radius+z) in
  let decomposition = assoc_add (factors1, factors2) in
  let pairs =
    if radius = z then PS.singleton (0, 0)
    else
      let ts = two_squares decomposition in
      if List.for_all (fun (_, q) -> q mod 2 = 0) decomposition then
        PS.add (0, List.fold_left (fun acc (p, q) -> acc * pow p (q/2)) 1 decomposition) ts
      else ts
  in
  let all_points points =
    let add f points =
      List.fold_left
      (fun acc p -> let fp = f p in if fp = p then p::acc else fp::p::acc)
      []
      points
    in
    let points = add (fun (x, y, z) -> -x, y, z) points in
    add (fun (x, y, z) -> x, z, y) points
  in
  all_points (PS.fold (fun (x, y) acc -> (z, x, y)::acc) pairs [])

let fold_seq f a b init =
  let rec aux acc a = if a > b then acc else aux (f acc a) (a+1) in
  aux init a

(* Use Dijkstra-like algorithm to find the shortest path. *)
let min_risk n =
  let radius = radius n in
  let add_z acc z = List.rev_append (solutions_for_z radius z) acc in
  let all_points = List.sort compare (fold_seq add_z 0 radius []) in
  let all_points = Array.of_list all_points in
  let nb_points = Array.length all_points in
  let risk = Array.make nb_points max_float in
  let is_done = Array.make nb_points false in 
  risk.(0) <- 0.0;
  let rec aux index =
    is_done.(index) <- true;
    if index = nb_points - 1 then risk.(index)
    else
      let current_risk = risk.(index) in
      let current_min = ref max_float in
      let where_min = ref 0 in
      for i = 0 to nb_points - 1 do
        if not is_done.(i) then (
          let r = crisk radius all_points.(i) all_points.(index) in
          risk.(i) <- min risk.(i) (current_risk +. r);
          if risk.(i) < !current_min then (
            current_min := risk.(i);
            where_min := i;
          )
        )
      done;
      aux !where_min
  in
  let res = aux 0 in
  Format.printf "%6d %6d %.10f@." radius nb_points res;
  res
;;
Format.printf "%.10f\n" (fold_seq (fun acc n -> acc +. min_risk n) 1 15 0.)

