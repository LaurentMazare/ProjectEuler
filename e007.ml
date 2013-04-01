let nth_prime n =
  let max_p = 10_000_000 in
  let is_prime, primes = Array.make (max_p+1) true, ref [] in
  for i = 2 to max_p do
    if is_prime.(i) then
      let rec aux j =
        if j <= max_p then (
          is_prime.(j) <- false;
          aux (j+i)
        )
      in (
        primes := i::!primes;
        aux (i+i)
      )
  done;
  let primes = List.rev !primes in
  List.nth primes (n-1)

let () = Format.printf "%d\n" (nth_prime 10_001)

