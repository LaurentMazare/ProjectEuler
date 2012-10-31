(* f(n)/f(n-1) is tightly linked to Stern-Brocot trees.
 * This implements a bisection search in such a tree returning
 * the binary path. *)

let rec gcd a b =
  if b = 0 then a else gcd b (a mod b)

let bisection (num, den) =
  let g = gcd num den in
  let num, den = num / g, den / g in
  let f = float_of_int num /. float_of_int den in
  let rec aux acc (lo_num, lo_den) (up_num, up_den) =
    let mid_num = lo_num + up_num in
    let mid_den = lo_den + up_den in
    let gcd = gcd mid_num mid_den in
    let mid_num = mid_num / gcd in
    let mid_den = mid_den / gcd in
    if mid_num = num && mid_den = den then acc
    else if f > float_of_int mid_num /. float_of_int mid_den then
      aux (0::acc) (mid_num, mid_den) (up_num, up_den)
    else
      aux (1::acc) (lo_num, lo_den) (mid_num, mid_den)
  in
  1::aux [] (0, 1) (1, 0)

let shortened_string l =
  let rec shorten acc last_elem list =
    match last_elem, list with
    | None, [] -> acc
    | Some (_, nb), [] -> nb::acc
    | None, p::q -> shorten acc (Some (p, 1)) q 
    | Some (p', nb), p::q when p' = p ->
        shorten acc (Some (p, nb+1)) q
    | Some (_, nb), p::q ->
        shorten (nb::acc) (Some (p, 1)) q
  in
  let shorten_str = List.rev_map string_of_int (shorten [] None l) in
  String.concat "," shorten_str

let () =
  let l = bisection (13, 17) in
  Format.printf "%s\n" (shortened_string l);
  let l = bisection (123456789, 987654321) in
  Format.printf "%s\n" (shortened_string l);;
