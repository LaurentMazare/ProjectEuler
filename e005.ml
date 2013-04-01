let rec gcd a b =
  if b = 0 then a else gcd b (a mod b)

let rec foldi f acc lo up =
  if up < lo then acc else foldi f (f acc lo) (lo+1) up

let () =
  let fmult acc x = acc * x / gcd acc x in
  Format.printf "%d" (foldi fmult 1 1 20)
