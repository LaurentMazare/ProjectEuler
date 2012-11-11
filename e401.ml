let m x = x mod 1000_000_000

let loop_sum low up f =
  let rec aux acc low = if low > up then acc else aux (m (acc + f low)) (low + 1) in
  aux 0 low

let sum_squares n = (* (n*(n+1)*(2n+1)) % 10**9 *)
  let f (acc, (div2, div3)) factor =
    let factor, div2 =
      if div2 && factor mod 2 = 0 then factor/2, false else factor, div2
    in
    let factor, div3 =
      if div3 && factor mod 3 = 0 then factor/3, false else factor, div3
    in
    (m (acc * m factor), (div2, div3))
  in
  fst (List.fold_left f (1, (true, true)) [n; n+1; (2*n+1)])

let sum_sigma2 n =
  let n_inter = int_of_float (sqrt (float_of_int n)) in
  let f1 x = sum_squares (n / x) in
  let f2 x = m (x * x) * m (max 0 (n / x - n_inter)) in
  m (loop_sum 1 n_inter f1 + loop_sum 1 (n / n_inter + 1) f2)
;;
Format.printf "%d\n" (sum_sigma2 1000_000_000_000_000)
