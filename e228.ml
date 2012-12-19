(* Geometric solution using Minkowski sums.
 * Note that there are some one line solutions far more efficient than this. *)

let pi = 4.0 *. atan 1.0
let cart_of_polar (rho, theta) = rho *. cos theta, rho *. sin theta
let polar_of_cart (x, y) =
  let rho = sqrt (x *. x +. y *. y) in
  rho, acos (x /. rho) +. if y < 0.0 then pi else 0.0

let rec last = function
  | [] -> failwith "Empty list"
  | [p] -> p
  | _::q -> last q

let same_side p1 p2 p3 = (* Returns true if p2 is on the same side of [p1, p3] as (0, 0). *)
  let (x1, y1), (x2, y2), (x3, y3) = cart_of_polar p1, cart_of_polar p2, cart_of_polar p3 in
  let dx, dy = x3 -. x1, y3 -. y1 in
  ((-.x1) *. dy +. y1 *. dx) *. ((x2 -. x1) *. dy -. (y2 -. y1) *. dx) >= -1.0e-14

let poly n = Array.to_list (Array.init n (fun k -> (1.0, pi *. float_of_int (2*k+1) /. float_of_int n)))

let cleanup l = (* Remove points that are inside the convex hull. *)
  let first_point, last_point = List.hd l, last l in
  let rec aux prev acc = function
    | [] -> acc
    | [p] -> if same_side prev p first_point then acc else p::acc
    | p1::p2::q ->
        let acc = if same_side prev p1 p2 then acc else p1::acc in
        aux p1 acc (p2::q)
  in
  aux last_point [] l

let sort l = List.sort (fun (_, x) (_, y) -> if x > y then 1 else if x = y then 0 else -1) l
let add s1 s2 =
  let rec aux acc = function
    | [], _ -> acc
    | p::q, (p1::p2::qq as ll) when snd p1 < snd p && snd p < snd p2 ->
        let (x, y), (x1, y1), (x2, y2) = cart_of_polar p, cart_of_polar p1, cart_of_polar p2 in
        aux ((x+.x1, y+.y1)::(x+.x2, y+.y2)::acc) (q, ll)
    | l, _::qq -> aux acc (l, qq)
    | _, [] -> failwith "Empty list"
  in
  let (lrho, ltheta), (frho, ftheta) = last s2, List.hd s2 in
  let s2 = (lrho, ltheta -. 2.0 *. pi)::s2 @ [frho, ftheta +. 2.0 *. pi] in
  sort (cleanup (sort (List.map polar_of_cart (aux [] (s1, s2)))))

let fold_int f start x y =
  let rec aux acc x = if x > y then acc else aux (f acc x) (x+1) in
  aux start x

let () =
  let s = fold_int (fun acc i -> add acc (poly i)) (poly 1864) 1865 1909 in
  Format.printf "%d\n" (List.length s)
