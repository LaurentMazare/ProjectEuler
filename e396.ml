(* Weak Goodstein sequence length
 * As seen on http://en.wikipedia.org/wiki/Goodstein's_theorem,
 * G(2^m1+2^m2+...+2^mk) = f_m1(f_m2(...f_mk(3))) - 3
 * m1 > m2 > ... > mk
 * Run command: ocamlopt.opt e396.ml -o e396 && time ./e396
 *)
let rec pow_mod x n m =
  if n = 0 then 1
  else if n mod 2 = 0 then let x = pow_mod x (n/2) m in (x*x) mod m
  else (x * pow_mod x (n-1) m) mod m

let m = 1_000_000_000
let b2 x = (* Returns [mk; ...; m2; m1] if x = 2^m1+2^m2+...+2^mk *)
  let rec aux acc nb x =
    if x = 0 then acc
    else
      let acc = if x mod 2 = 1 then nb::acc else acc in
      aux acc (nb+1) (x/2)
  in
  List.rev(aux [] 0 x)

let rec iter n fn x =
  if n = 0 then x else (fn (iter (n-1) fn x)) mod m

let rec f k n = (* From http://en.wikipedia.org/wiki/Fast-growing_hierarchy *)
  if k = 0 then (n + 1) mod m
  else if k = 1 then (2 * n) mod m
  else if k = 2 then (pow_mod 2 n m * n) mod m
  else iter n (f (k-1)) n

let g x =
  List.fold_left (fun acc k -> f k acc) 3 (b2 x) - 3

let rec fold_int f a b init =
  if a > b then init else fold_int f (a+1) b (f init a)

let () =
  Format.printf "%d@." (g 6);
  let add_g acc n = let g = g n in Format.printf "%d %d@." n g; acc + g in
  let s = fold_int add_g 1 15 0 in
  Format.printf "%d\n" (s mod m)
