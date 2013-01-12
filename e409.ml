let md x =
  let m = x mod 1_000_000_007 in
  if m < 0 then m + 1_000_000_007 else m

let rec pow_mod x n =
  if n = 0 then 1
  else if n mod 2 = 0 then let p = pow_mod x (n/2) in md (p*p)
  else md (x * pow_mod x (n-1))

let nb_nim n =
  let two_n = pow_mod 2 n in
  let rec aux m a c prod =
    if m > n then a
    else
      let a, c = (prod+c-a) * (two_n-m) + (a-c) * (two_n-m-1), md (m * (prod-a)) * (two_n-m) in
      aux (m+1) (md a) (md c) (md (prod * (two_n-m)))
  in
  aux 2 (two_n-1) (two_n-1) (two_n-1)

let () = Format.printf "%d\n" (nb_nim 10_000_000)
