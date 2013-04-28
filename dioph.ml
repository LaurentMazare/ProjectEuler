let rec gcd x y = if y = 0 then x else gcd y (x mod y)

let rec extended_gcd x y =
  if y = 0 then 1, 0
  else
    let q = x / y in
    let s, t = extended_gcd y (x - q*y) in
    t, s - q*t

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

type prime_decomposition = (int * int) list

(* Takes as input the prime decomposition for n as an assoc list and returns
 * a set of all the pairs (a, b) such that n = a^2 + b^2. *)
let two_squares factors =
  let fact3 = List.filter (fun (x, _) -> x mod 4 = 3) factors in
  let fact1 = List.filter (fun (x, _) -> x mod 4 = 1) factors in
  let fact2 = List.filter (fun (x, _) -> x = 2) factors in
  let fact1 = expand_assoc fact1 in
  if List.exists (fun (_, q) -> q mod 2 = 1) fact3 then []
  else
    let mult, fact1 =
      match fact2 with
      | [p, q] when q mod 2 = 1 -> (pow 2 (q/2)), 2::fact1
      | [p, q] when q mod 2 = 0 -> (pow 2 (q/2)), fact1
      | _ -> 1, fact1
    in
    let pairs = two_squares_ fact1 in
    let mult = mult * List.fold_left (fun acc (p, q) -> acc * pow p (q/2)) 1 fact3 in
    let set = PS.fold (fun (x, y) acc -> PS.add (mult * min x y, mult * max x y) acc) pairs PS.empty in
    PS.fold (fun elm acc -> elm::acc) set []

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

let sqrt_int x =
  let open Z in
  let sqrt_x = Z.sqrt x in
  if sqrt_x * sqrt_x = x then Some sqrt_x else None

(* The Pell solvers and PQa algorithm below come from:
 * http://www.jpr2718.org/pell.pdf
 *)
let pqa p0 q0 d =
  let open Z in
  let sqrt_d = Pervasives.sqrt (to_float d) in
  let rec aux a_i a_im b_i b_im g_i g_im p_i q_i i start alphas =
    let i = succ i in
    let float_pi, float_qi = to_float p_i, to_float q_i in
    let xi_i = (float_pi +. sqrt_d) /. float_qi in
    let xibar_i = (float_pi -. sqrt_d) /. float_qi in
    let alpha_i = of_float xi_i in
    let a_i, a_im = alpha_i * a_i + a_im, a_i in
    let b_i, b_im = alpha_i * b_i + b_im, b_i in
    let g_i, g_im = alpha_i * g_i + g_im, g_i in
    (* Everything is now as of i. *)
    match start with
    | Some (ir, p_ir, q_ir) when p_ir = p_i && q_ir = q_i ->
        alphas, i - ir
    | _ ->
      let alphas = alpha_i::alphas in
      let start =
        match start with
        | Some _ -> start
        | None ->
            if 1. < xi_i && -1. < xibar_i && xibar_i < 0. then Some (i, p_i, q_i)
            else None
      in
      (* Update p_i and q_i for i+1. *)
      let p_i = alpha_i * q_i - p_i in
      let q_i = (d - p_i * p_i) / q_i in
      aux a_i a_im b_i b_im g_i g_im p_i q_i i start alphas
  in
  let alphas, l = aux one zero zero one q0 (-p0) p0 q0 minus_one None [] in
  List.rev alphas, to_int l

let pell1_min d pos =
  let alphas, l = pqa Z.zero Z.one d in
  let l_is_even = l mod 2 == 0 in
  if l_is_even && not pos then
    None
  else 
    let index = if l_is_even then l-1 else if pos then 2*l-1 else l-1 in
    let alphas = Array.of_list alphas in
    let pre_l = Array.length alphas - l in
    let rec aux b_i b_im g_i g_im i =
      if i = index + 1 then g_i, b_i
      else
        let idx = if i < pre_l then i else pre_l + (i-pre_l) mod l in
        let alpha_i = alphas.(idx) in
        let b_i, b_im = Z.(alpha_i * b_i + b_im, b_i) in
        let g_i, g_im = Z.(alpha_i * g_i + g_im, g_i) in
        aux b_i b_im g_i g_im (i+1)
      in
    Some (aux Z.zero Z.one Z.one Z.zero 0)

(* Iterators as lazy list. *)
type 'a iterator_ =
  | I_end
  | I_elt of 'a * 'a iterator
and 'a iterator = unit -> 'a iterator_

let takewhile it predicate =
  let rec aux acc = function
    | I_end -> acc
    | I_elt (elt, next) ->
        if predicate elt then
          aux (elt::acc) (next ())
        else acc
  in
  List.rev (aux [] (it ()))

(* Yield all the solutions (x, y) for x^2 - d.y^2 = eps, where eps is 1 if pos is true, -1 otherwise. *)
let pell1_it d pos =
  match pell1_min d pos with
  | None -> fun () -> I_end
  | Some (t, u) ->
      let rec next x y =
        fun () ->
          let elt = x, y in
          let x, y = Z.(t*x + u*y*d, t*y + u*x) in
          let x, y = if not pos then Z.(t*x + u*y*d, t*y + u*x) else x, y in
          I_elt (elt, next x y)
      in
      next t u

(* Yield all the solutions (x, y) for x^2 - d.y^2 = eps, where eps is 1 if pos is true,
 * -1 otherwise such that x <= max_x. *)
let pell1 d pos max_x =
  takewhile (pell1_it d pos) (fun (x, _) -> x <= max_x)

let fold_zint f acc lo up =
  let rec aux acc n =
    if up < n then acc
    else aux (f acc n) Z.(n + one)
  in
  aux acc lo

let two = Z.of_int 2

(* Brute-force solver to obtain fundamental solutions of the generalized Pell
 * equation: x^2 - d.y^2 = n. *)
let pell_funds_bf d n =
  match pell1_min d true with
  | None -> assert false (* x^2 - d.y^2 always has solutions if d is not a perfect square. *)
  | Some (t, u) ->
      let l1, l2 =
        let nf, tf, df = Z.to_float n, Z.to_float t, Z.to_float d in
        if Z.zero < n then Z.zero, Z.of_float (sqrt ((nf*.(tf-.1.)) /. (2.*.df)))
        else
          Z.of_float (sqrt (-.nf/.df)), Z.of_float (sqrt ((-.nf*.(tf+.1.)) /. (2.*.df)))
      in
      let open Z in
      let f acc y =
        match sqrt_int (n + d*y*y) with
        | None -> acc
        | Some x ->
          if x*x+d*y*y mod n = zero && (two*x*y) mod n = zero then
            (x, y)::acc
          else
            (-x, y)::(x, y)::acc
      in
      fold_zint f [] l1 l2

module ZPS = Set.Make(
  struct
    let compare = Pervasives.compare
    type t = Z.t * Z.t
  end )

let pell pell_funds d n max_x =
  let open Z in
  let funds = pell_funds d n in
  let add_funds acc (x, y) = ZPS.add (abs x, abs y) acc in
  let sols = List.fold_left add_funds ZPS.empty funds in
  let it = pell1_it d true in
  let rec aux acc = function
    | I_end -> acc
    | I_elt ((t, u), next) ->
        let add_funds (added, acc) (r, s) =
          let x, y = r*t + s*u*d, r*u + s*t in
          if abs x <= max_x then
            true, ZPS.add (abs x, abs y) acc
          else added, acc
        in
        let added, acc = List.fold_left add_funds (false, acc) funds in
        if added then aux acc (next ()) else acc
  in
  let sols = aux sols (it ()) in
  let sols = ZPS.fold (fun e acc -> e::acc) sols [] in
  List.sort Pervasives.compare sols

let pell_bf d n max_x = pell pell_funds_bf d n max_x

let pqa_lmm p0 q0 d =
  let open Z in
  let sqrt_d = Pervasives.sqrt (to_float d) in
  let rec aux a_i a_im b_i b_im g_i g_im p_i q_i i start =
    let i = succ i in
    let float_pi, float_qi = to_float p_i, to_float q_i in
    let xi_i = (float_pi +. sqrt_d) /. float_qi in
    let xibar_i = (float_pi -. sqrt_d) /. float_qi in
    let alpha_i = of_float xi_i in
    let a_i, a_im = alpha_i * a_i + a_im, a_i in
    let b_i, b_im = alpha_i * b_i + b_im, b_i in
    let g_i, g_im = alpha_i * g_i + g_im, g_i in
    (* Everything is now as of i. *)
    match start with
    | Some (p_ir, q_ir) when p_ir = p_i && q_ir = q_i -> None
    | _ ->
      let start =
        match start with
        | Some _ -> start
        | None ->
            if 1. < xi_i && -1. < xibar_i && xibar_i < 0. then Some (p_i, q_i)
            else None
      in
      (* Update p_i and q_i for i+1. *)
      let p_i = alpha_i * q_i - p_i in
      let q_i = (d - p_i * p_i) / q_i in
      if abs q_i = one then Some (g_i, b_i)
      else aux a_i a_im b_i b_im g_i g_im p_i q_i i start
  in
  aux one zero zero one q0 (-p0) p0 q0 minus_one None

let filter_double d n l =
  let open Z in
  let rec aux acc = function
    | [] -> acc
    | (x, y)::q ->
        let min_sol =
          List.fold_left
          (fun acc (r, s) ->
            if (x*r - d*y*s) mod n = zero && (x*s - y*r) mod n = zero && abs r <= abs x then false
            else acc
          )
          true
          q
        in
        let acc = if min_sol then (x, y)::acc else acc in
        aux acc q
  in
  aux [] l

(* Lagrange-Matthews-Mollin algorithm, once again as described in:
 * http://www.jpr2718.org/pell.pdf
 * Note that this version is not very efficient as the square root are computed
 * in a brute force way.
 *)
let pell_funds_lmm d n =
  let open Z in
  let add_f acc f =
    if n mod (f*f) = zero then
      let m = n / (f*f) in
      let abs_m = abs m in
      let add_z acc z =
        if (z * z - d) mod abs_m = zero then
          match pqa_lmm z abs_m d with
          | None -> acc
          | Some (r, s) ->
              let res = r*r - d*s*s in
              if res = m then (f*r, f*s)::acc
              else if res = -m then
                match pell1_min d false with
                | None -> acc
                | Some (t, u) -> (f*(r*t+s*u*d), f*(r*u+s*t))::acc
              else assert false
        else acc
      in
      fold_zint add_z acc (one-abs_m) abs_m
    else acc
  in
  filter_double d n (fold_zint add_f [] one (sqrt n))

let pell_lmm d n max_x = pell pell_funds_lmm d n max_x

let quad_s a b c max_x =
  let open Z in
  let res = pell_bf (a*b) (a*c) (a*max_x) in
  let add_res acc (x, y) =
    let x, rem = div_rem x a in
    if rem = zero then (x, y)::acc else acc
  in
  List.fold_left add_res [] res


