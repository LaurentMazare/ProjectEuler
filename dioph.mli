(* [gcd x y] returns the greatest common divisor between x and y using Euclid's
 * algorithm. *)
val gcd : int -> int -> int

(* [extended_gcd x y] returns a pair of coefficient (a, b) that satisfies
 * Bezout's identity: a.x + b.y = gcd x y. *)
val extended_gcd : int -> int -> int * int

(* [pow x n] returns x^n. *)
val pow : int -> int -> int

(* [pow_mod x n m] returns x^n % m. *)
val pow_mod : int -> int -> int -> int

(* [sqrt_m1 p] returns the square root of -1 modulo a prime p. This uses a
 * rather brute-force method and so is quite inefficient compared to the
 * Tonelli-Shank's method. *)
val sqrt_m1 : int -> int

(* A prime decomposition of n is a list of pair (p_i, q_i) where:
 * n = prod_i p_i^q_i. *)
type prime_decomposition = (int * int) list

(* [prime_decomposition max_n] returns a function that takes as argument an
 * integer n up to max_n and returns the prime decomposition of n. *)
val prime_decomposition : int -> int -> prime_decomposition

(* [two_squares pd] takes as argument the prime decomposition pd of an integer n
 * and returns all the two square decompositions (x, y) such that:
 * n = x^2 + y^2. The empty list is returned if no such pair exists. *)
val two_squares : prime_decomposition -> (int * int) list

(* [sqrt_int x] returns Some y such that y*y = x if x is a perfect square. None
 * is returned otherwise. *)
val sqrt_int: Z.t -> Z.t option

(* [pqa p0 q0 d] applies the PQa algorithm. It outputs a pair alphas, l
 * representing the continued fraction for (p0+sqrt(d))/q0. alphas are the
 * continued fraction coefficients, the last l elements are repeating
 * indefinitely (as the continued fraction is periodic).
 * See http://www.jpr2718.org/pell.pdf for details. *)
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

(* Iterator version that returns the infinite sequence. *)
val pell1_it: Z.t -> bool -> (Z.t * Z.t) iterator

(* [pell1 d pos] returns the minimum solution for the related Pell equation:
 * x^2 - d.y^2 = +/-1. *)
val pell1_min: Z.t -> bool -> (Z.t * Z.t) option

(* [pell_bf d n max_x] returns all the positive solutions (x, y)
 * with x <= max_x for the generalized Pell equation: x^2 - d.y^2 = n.
 * The fundamental solutions are generated with a brute-force approach.
 *) 
val pell_bf : Z.t -> Z.t -> Z.t -> (Z.t * Z.t) list

(* [pell_funds_bf d n] return all the fundamental solutions for the generalized
 * Pell equation: x^2 - d.y^2 = n. *)
val pell_funds_bf : Z.t -> Z.t -> (Z.t * Z.t) list

(* [pell_lmm d n max_x] returns all the positive solutions (x, y)
 * with x <= max_x for the generalized Pell equation: x^2 - d.y^2 = n.
 * The fundamental solutions are generated with a naive version of the LMM
 * algorithm.
 *) 
val pell_lmm : Z.t -> Z.t -> Z.t -> (Z.t * Z.t) list
val pell_funds_lmm : Z.t -> Z.t -> (Z.t * Z.t) list

(* [quad_s a b c max_x] returns all the positive solutions (x, y)
 * with x <= max_x for equation a.x^2 - b.y^2 = c. *)
val quad_s : Z.t -> Z.t -> Z.t -> Z.t -> (Z.t * Z.t) list
