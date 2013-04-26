val gcd : int -> int -> int
val extended_gcd : int -> int -> int * int
val pow : int -> int -> int
val pow_mod : int -> int -> int -> int
val sqrt_m1 : int -> int
type prime_decomposition = (int * int) list
val two_squares : prime_decomposition -> (int * int) list
val prime_decomposition : int -> int -> prime_decomposition

val sqrt_int: int -> int option
val pqa : int -> int -> int -> int list * int

(* [pell1 d pos max_x] returns all the positive solutions (x, y)
 * for equation x^2 - d.y^2 = 1 if pos is true else -1. *)
val pell1 : int -> bool -> int -> (int * int) list

