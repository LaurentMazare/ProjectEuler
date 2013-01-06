let rec fold_int f acc x y =
  if x > y then acc else fold_int f (f acc x) (x+1) y

let rec pow x n =
  if n = 0 then 1
  else if n mod 2 = 0 then let p = pow x (n/2) in p * p
  else x * pow x (n-1)

let lim = 100
let one_root a d = 
  let cache = Hashtbl.create 4 in
  let rec one_root down up = function
    | 0 -> max 0 (1 + min (9/a) up - max 1 down)
    | d ->
        let key = down, up, d in
        if Hashtbl.mem cache key then Hashtbl.find cache key
        else
          let f acc lambda = acc + one_root (max (-lim) (-a*lambda)) (min lim (9-a*lambda)) (d - 1) in
          let res = fold_int f 0 down up in
          Hashtbl.add cache key res;
          res
  in
  one_root 0 9 d

let div_up x y = if x >= 0 then (x + y - 1) / y else x / y
let div_down x y = if x >= 0 then x / y else (x - y + 1) / y

let two_roots a1 a2 d = 
  let cache = Hashtbl.create 4 in
  let rec two_roots prev_l down up = function
    | 0 ->
        let lmin = div_up (- prev_l * a1 * a2) (a1 + a2) in
        let lmax = div_down (9 - prev_l * a1 * a2) (a1 + a2) in
        let lmin = max 1 (max down lmin) in
        let lmax = min (9/(a1*a2)) (min up lmax) in
        max 0 (1 + lmax - lmin)
    | d ->
        let key = prev_l, down, up, d in
        if Hashtbl.mem cache key then Hashtbl.find cache key
        else
          let f acc lambda =
            let shift = lambda * (a1+a2) + prev_l * a1 * a2 in
            acc + two_roots lambda (max (-lim) (-shift)) (min lim (9-shift)) (d-1)
          in
          let res = fold_int f 0 down up in
          Hashtbl.add cache key res;
          res
  in
  two_roots 0 0 9 d

let three_roots a1 a2 a3 d = 
  let cache = Hashtbl.create 4 in
  let s1, s2, s3 = a1+a2+a3, a1*a2+a1*a3+a2*a3, a1*a2*a3 in
  let rec three_roots prev_l2 prev_l down up = function
    | 0 ->
        let lmin = div_up (- prev_l * s3) s2 in
        let lmax = div_down (9 - prev_l * s3) s2 in
        let lmin = max lmin (div_up (-prev_l*s2-prev_l2*s3) s1) in
        let lmax = min lmax (div_down (9-prev_l*s2-prev_l2*s3) s1) in
        let lmin = max 1 (max down lmin) in
        let lmax = min (9/s3) (min up lmax) in
        max 0 (1 + lmax - lmin)
    | d ->
        let key = prev_l, down, up, d in
        if Hashtbl.mem cache key then Hashtbl.find cache key
        else
          let f acc lambda =
            let shift = lambda * s1 + prev_l * s2 + prev_l2 * s3 in
            acc + three_roots prev_l lambda (max (-lim) (-shift)) (min lim (9-shift)) (d-1)
          in
          let res = fold_int f 0 down up in
          Hashtbl.add cache key res;
          res
  in
  three_roots 0 0 0 9 d

let nb_sols n =
  (* Inclusion-exclusion, add roots -1 to -9, remove polynomials with two roots. *)
  let roots_1 = fold_int (fun acc a -> acc + one_root a (n-2)) 0 1 9 in
  let roots_2 = fold_int (fun acc a -> acc + two_roots 1 a (n-3)) 0 2 9 + two_roots 2 3 (n-3) + two_roots 2 4 (n-3) in
  let roots_3 = three_roots 1 2 3 (n-4) + three_roots 1 2 4 (n-4) in
  pow 10 (n-1) + roots_1 - roots_2 + roots_3

let () = Format.printf "%d\n" (nb_sols 16)
