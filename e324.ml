(* From OEIS 028452,
 * a(n)=679a(n-1) -76177a(n-2) +3519127a(n-3) -85911555a(n-4) +1235863045a(n-5)
 * -11123194131a(n-6) +65256474997a(n-7) -257866595482a(n-8) +705239311926a(n-9)
 * -1363115167354a(n-10) +1888426032982a(n-11) -1888426032982a(n-12)
 * +1363115167354a(n-13) -705239311926a(n-14) +257866595482a(n-15)
 * -65256474997a(n-16) +11123194131a(n-17) -1235863045a(n-18) +85911555a(n-19)
 * -3519127a(n-20) +76177a(n-21) -679a(n-22) +a(n-23)
 *)
let md x = x mod 100000007
let mult_mod a b =
  let n = Array.length a in
  let prod i j =
    let rec sum acc = function
      | m when m = n -> acc
      | k -> sum (md (acc + a.(i).(k) * b.(k).(j))) (k+1)
    in
    sum 0 0
  in
  Array.init n (fun i -> Array.init n (prod i))

let mult_vec a v =
  let n = Array.length a in
  let prod i =
    let rec sum acc = function
      | m when m = n -> acc
      | k -> sum (md (acc + a.(i).(k) * v.(k))) (k+1)
    in
    sum 0 0
  in
  Array.init n prod

let bi_zero = Big_int.big_int_of_int 0;;
let bi_one = Big_int.big_int_of_int 1;;
let bi_two = Big_int.big_int_of_int 2;;
let rec pow_mod a = function
  | n when Big_int.eq_big_int n Big_int.unit_big_int -> a
  | n when Big_int.eq_big_int (Big_int.mod_big_int n bi_two) bi_zero ->
      let a = pow_mod a (Big_int.div_big_int n bi_two) in
      mult_mod a a
  | n -> mult_mod (pow_mod a (Big_int.sub_big_int n bi_one)) a

let cache = Hashtbl.create 4
let rec f heights =
  let max_min (x, y) h = (max x h), (min y h) in
  let max, min = Array.fold_left max_min (-1, max_int) heights in
  if min < 0 then 0
  else if max == 0 then 1
  else if Hashtbl.mem cache heights then Hashtbl.find cache heights
  else
    let where_max = ref 0 in
    Array.iteri (fun i h -> if h == max then where_max := i) heights;
    let where_max = !where_max in
    let add_comb dir =
      let next = where_max + dir in
      if next < 0 || next > 8 || (abs dir == 1 && next / 3 != where_max / 3) || heights.(next) != max then
        0
      else (
        heights.(where_max) <- max - 1;
        heights.(next) <- max - 1;
        let res = f heights in
        heights.(where_max) <- max;
        heights.(next) <- max;
        res
      )
    in
    let add2 =
      if max >= 2 then (
        heights.(where_max) <- max - 2;
        let res = f heights in
        heights.(where_max) <- max;
        res
      )
      else 0
    in
    let res = add2 + add_comb (-1) + add_comb 1 + add_comb (-3) + add_comb 3 in
    let res = md res in
    Hashtbl.add cache (Array.copy heights) res;
    res

let () =
  let a = Array.init 23 (fun i -> let x = Array.make 23 0 in if i < 22 then x.(i+1) <- 1; x) in
  a.(22) <- Array.map md [| 1; -679; 76177; -3519127; 85911555; -1235863045; 11123194131;
    -65256474997; 257866595482; -705239311926; 1363115167354;
    -1888426032982; 1888426032982; -1363115167354; 705239311926;
    -257866595482; 65256474997; -11123194131; 1235863045; -85911555; 3519127;
    -76177; 679 |];
  let f i = f (Array.make 9 (2*i)) in
  Printf.printf "%d\n" (f 23);
  let vec = Array.init 23 f in
  let n = Big_int.div_big_int (Big_int.power_int_positive_int 10 10000) bi_two in
  let a_n = pow_mod a n in
  let vec = mult_vec a_n vec in
  Printf.printf "%d\n" vec.(0)
