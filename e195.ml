let rec gcd a b = if b = 0 then a else gcd b (a mod b)

let () =
  let max_r = 1053779.0 in
  let count m n =
    if m mod 3 = n mod 3 || gcd m n > 1 then None
    else
      let m2 = m * m and n2 = n * n and mn = m * n in
      let z = m2 + n2 + mn in
      let nb_sol x y =
        let xf = float_of_int x and yf = float_of_int y and zf = float_of_int z in
        let s = (xf +. yf +. zf) /. 2.0 in
        let r = sqrt((s -. xf) *. (s -. yf) *. (s -. zf) /. s) in
        int_of_float (max_r /. r)
      in
      Some (nb_sol (2*mn + m2) (2*mn + n2) + nb_sol (2*mn + m2) (m2 - n2))
  in
  let extr o = match o with | None -> 0 | Some c -> c in
  let rec aux_loop acc m n =
    let count = count m n in
    if count = Some 0 then
      if m = n + 1 then acc
      else aux_loop acc (n+2) (n+1)
    else aux_loop (acc + extr count) (m+1) n
  in
  Format.printf "%d\n" (aux_loop 0 2 1)
;;

