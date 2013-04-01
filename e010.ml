let sum_prime max_p =
  let is_prime, sum = Array.make (max_p+1) true, ref 0 in
  for i = 2 to max_p do
    if is_prime.(i) then
      let rec aux j =
        if j <= max_p then (
          is_prime.(j) <- false;
          aux (j+i)
        )
      in (
        sum := !sum + i;
        aux (i+i)
      )
  done;
  !sum

let () = Format.printf "%d\n" (sum_prime 2_000_000)
