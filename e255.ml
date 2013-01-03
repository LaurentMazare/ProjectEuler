let rec digits n = if n = 0 then 0 else 1 + digits (n/10)
let rec ten n = if n = 0 then 1 else 10 * ten (n-1)
let it n = (* Computes the number of iterations for rounded sqrt. *)
  let rec aux prev_x x k =
    if x = prev_x then k, x
    else aux x ((x + (n+x-1) / x) / 2) (k+1)
  in
  let d = digits n in
  let x0 = if d mod 2 = 1 then 2*ten (d/2) else 7*ten (d/2-1) in
  aux (-1) x0 0

let sum low up = (* Bisection method to sum it(n) for n in [low, up]. *)
  let rec bisection low up =
    let it_low, _ = it low in
    let it_up, _ = it up in
    if up < low then 0
    else if it_low = it_up then it_up * (up - low + 1)
    else if low + 1 = up then it_low + it_up
    else
      let mid = (low + up) / 2 in
      bisection low mid + bisection (mid+1) up
  in
  let rec aux acc i =
    let i2 = i * (i+1) + 1 in
    let ip2 = (i+1) * (i+2) in
    if ip2 > up then acc + bisection i2 up else aux (acc+bisection i2 ip2) (i+1)
  in
  let _, lo2 = it low in
  aux (bisection low (lo2*(lo2+1))) lo2

let () =
  let lo = ten 13 in
  let up = ten 14 - 1 in
  Format.printf "%.10f\n" ((float_of_int (sum lo up)) /. float_of_int (up - lo + 1))
