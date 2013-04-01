let fmax f lo up =
  let rec aux acc lo =
    if up < lo then acc else aux (max acc (f lo)) (lo+1)
  in
  aux 0 lo

let p n =
  let rec rev acc = function
    | 0 -> acc
    | n -> rev (acc*10 + n mod 10) (n/10)
  in
  if rev 0 n == n then n else 0

let () =
  Format.printf "%d\n" (fmax (fun i -> fmax (fun j -> p (i*j)) i 999) 100 999)
