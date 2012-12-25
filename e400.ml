(* Hackenbush Green tree using Conlon principle.
 * Run command: ocamlopt.opt e400.ml -o e400 && time ./e400 *)
let add_mod x y = (x + y) mod 1_000_000_000_000_000_000

let cache_fib = Hashtbl.create 4
(* Compute Grundig number for T(n) *)
let gfib n =
  if n = 1 then 1
  else if n = 2 then 2
  else if Hashtbl.mem cache_fib n then Hashtbl.find cache_fib n
  else
    let rec aux prev prev2 n =
      if n = 0 then prev else aux (1 + (lxor) prev prev2) prev (n-1)
    in
    let res = aux 2 1 (n-2) in
    Hashtbl.add cache_fib n res;
    res

let cache_moves = Hashtbl.create 4
let moves n =
  (* Returns the number of moves in T(n) such that the Grundig number will be g. *)
  let rec moves n g =
    if g = 0 then 1
    else if n = 1 then
      if g = 1 then 1 else 0
    else if n = 2 then
      if g = 2 || g = 1 then 1 else 0
    else if Hashtbl.mem cache_moves (n, g) then Hashtbl.find cache_moves (n, g)
    else
      let res =
        add_mod
          (moves (n-1) ((lxor) (g - 1) (gfib (n-2))))
          (moves (n-2) ((lxor) (g - 1) (gfib (n-1))))
      in
      Hashtbl.add cache_moves (n, g) res;
      res
  in
  moves n 1

let () = Format.printf "%d\n" (moves 10_000)
