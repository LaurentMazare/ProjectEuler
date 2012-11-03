(* Stern-Brocot tree based coprime iteration. *)
let stern_brocot max f init =
  let rec aux acc a b =
    if a > max || b > max then acc
    else
      let acc = aux (f acc a b) a (a+b) in
      aux acc b (a+b)
  in
  aux init 1 2

module Int2Set = Set.Make( 
  struct
    let compare = Pervasives.compare
    type t = int * int
  end )

let () =
  let max_r = 100.0 in
  let count acc n m =
    let m2 = m * m and n2 = n * n and mn = m * n in
    let x = abs (m2 - n2) in
    let y = abs (2 * mn - n2) in
    let x, y = min x y, max x y in
    let z = m2 + n2 - mn in
    if x = 0 || x = y || x*x + y*y - x*y != z*z then acc
    else
      let xf = float_of_int x and yf = float_of_int y and zf = float_of_int z in
      let s = (xf +. yf +. zf) /. 2.0 in
      let r = sqrt((s -. xf) *. (s -. yf) *. (s -. zf) /. s) in
      let rec aux acc mult =
        if float_of_int mult *. r > max_r then acc
        else aux (Int2Set.add (mult * x, mult * y) acc) (mult + 1)
      in
      aux acc 1
    in
  let count acc m n = count (count acc m n) n m in
  let all_elts = stern_brocot 500 count Int2Set.empty in
  let nb_elements = Int2Set.fold (fun _ acc -> acc + 1) all_elts 0 in
  Format.printf "%d\n" nb_elements
;;

