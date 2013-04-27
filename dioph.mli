val gcd : int -> int -> int
val extended_gcd : int -> int -> int * int
val pow : int -> int -> int
val pow_mod : int -> int -> int -> int
val sqrt_m1 : int -> int
type prime_decomposition = (int * int) list
val two_squares : prime_decomposition -> (int * int) list
val prime_decomposition : int -> int -> prime_decomposition

val sqrt_int: Z.t -> Z.t option
val pqa : Z.t -> Z.t -> Z.t -> Z.t list * int
(* Iterators as lazy list. *)
type 'a iterator_ =
  | I_end
  | I_elt of 'a * 'a iterator
and 'a iterator = unit -> 'a iterator_


(* [pell1 d pos max_x] returns all the positive solutions (x, y)
 * for equation x^2 - d.y^2 = 1 if pos is true else -1 such that
 * x <= max_x. *)
val pell1 : Z.t -> bool -> Z.t -> (Z.t * Z.t) list
(* Iterator version. *)
val pell1_it: Z.t -> bool -> (Z.t * Z.t) iterator

val pell1_min: Z.t -> bool -> (Z.t * Z.t) option

(* [pell_bf d n max_x] returns all the positive solutions (x, y)
 * with x <= max_x for the generalized Pell equation:
 * x^2 - d.y^2 = n.
 * The fundamental solutions are generated with a brute-force approach.
 *) 
val pell_bf : Z.t -> Z.t -> Z.t -> (Z.t * Z.t) list

val pell_funds_bf : Z.t -> Z.t -> (Z.t * Z.t) list

