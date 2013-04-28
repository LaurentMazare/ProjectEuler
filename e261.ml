(* This is equivalent to m.n^2 + m.(m+1).n = k^2.(m+1) + m.(m+1).k
 * And also to: m(2n+m+1)^2 - (m+1)(2k-m)^2 = m(m+1)
 * However because of sqrt precision issue on float (and also to speed up processing),
 * we simplify again the equation by noting that m divides k^2 so sqrt_(m) divides k
 * where sqrt_(p1^q1...pn^qn) = p1^((1+q1)/2)...pn^((1+qn)/2)
 * m(2n+m+1)^2/s_m - (m+1)(2k-m)^2.s_m = m(m+1)/s_m where s_m = sqrt_(m)
 * Then we iterate over m and solve the equation as a variation of Pell equation
 * using the algorithms implemented in dioph.ml.
 * Compile with the following command:
 * ocamlopt.opt -I +zarith zarith.cmxa bigarray.cmxa dioph.mli dioph.ml e261.ml -o e261
 *)
let fold_int f acc lo up =
  let rec aux acc n =
    if up < n then acc
    else aux (f acc n) (n+1)
  in
  aux acc lo

module ZS = Set.Make(
  struct
    let compare = Pervasives.compare
    type t = Z.t
  end )

let sqrt_ pd =
  let mult acc (p, q) =
    acc * Dioph.pow p ((q+1)/2)
  in
  List.fold_left mult 1 pd

let () =
  let open Z in
  let two = of_int 2 in
  let max_k = pow (of_int 10) 10 in
  let max_m = to_int (sqrt (max_k / two) + one) in
  let max_x = max_k * of_int 100 in
  let pd = Dioph.prime_decomposition max_m in
  let add_pivot acc m =
    let s_m = of_int (sqrt_ (pd m)) in
    let m = of_int m in
    let s = Dioph.quad_s (m/s_m) ((m+one)*s_m) (m/s_m*(m+one)) max_x in
    let add_one acc (x, y) =
      let two_n, two_k = x - m - one, y + m / s_m in
      if two_n mod two = zero && two_k mod two = zero then
        let n, k = two_n / two, s_m * two_k / two in
        if k <= n && k <= max_k then ZS.add k acc else acc
      else acc
    in
    List.fold_left add_one acc s
  in
  let pivots = fold_int add_pivot ZS.empty 1 max_m in
  let sum = ZS.fold (fun x acc -> x + acc) pivots zero in
  Format.printf "%s\n" (to_string sum)
