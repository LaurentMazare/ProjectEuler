let rec area depth k1 k2 k3 =
  if depth = 0 then 0.
  else
    let k = k1 +. k2 +. k3 +. 2. *. sqrt (k1*.k2 +. k2*.k3 +. k1*.k3) in
    let r = 1. /. k in
    let area = area (depth - 1) in
    r *. r +. area k1 k2 k +. area k2 k3 k +. area k1 k3 k

(* Straightforward application of Descarte's Theorem *)
let () =
  let k0 = -. 1. in (* Main circle as radius 1 and curvature -1 *)
  let k1 = (6. +. sqrt 48.) /. 6. in (* Three biggest inner circles *)
  let area = area 10 in
  let area1 = (1. /. k1) *. (1. /. k1) in
  let total = area k1 k1 k1 +. 3. *. area k1 k1 k0 +. 3. *. area1 in
  Format.printf "%.8f\n" (1. -. total)
;;
