let dtheta = acos (4. /. 5.)
let pi = 4. *. atan 1.
let min_list = List.fold_left min max_float
let max_list = List.fold_left max (-. max_float)

let rec f theta n =
  let cosT, sinT = cos theta, sin theta in
  let x1, y1 = 0., 0. in
  let x2, y2 = cosT, sinT in
  let x3, y3 = cosT -. sinT, cosT +. sinT in
  let x4, y4 = -. sinT, cosT in
  let x_list, y_list =
    match n with
    | 1 -> [x1; x2; x3; x4], [y1; y2; y3; y4]
    | n ->
        let theta' = theta +. dtheta in
        let theta' = if theta' > 2. *. pi then theta' -. 2. *. pi else theta' in
        let x5, y5 = x4 +. 0.8 *. cos theta', y4 +. 0.8 *. sin theta' in
        let min_x, min_y, max_x, max_y = f theta' (n-1) in
        let x_list = [x1; x2; x3; x4; x4 +. 0.8 *. min_x; x4 +. 0.8 *. max_x; x5 +. 0.6 *. min_y; x5 +. 0.6 *. max_y] in
        let y_list = [y1; y2; y3; y4; y4 +. 0.8 *. min_y; y4 +. 0.8 *. max_y; y5 -. 0.6 *. max_x; y5 -. 0.6 *. min_x] in
        x_list, y_list
  in
  min_list x_list, min_list y_list, max_list x_list, max_list y_list

let min_x, min_y, max_x, max_y = f 0.0 100;;
Format.printf "Area: %.10f\n" ((max_y -. min_y) *. (max_x -. min_x))
