(* Compile with the following command:
 * ocamlopt.opt -I +zarith zarith.cmxa bigarray.cmxa dioph.mli dioph.ml dioph_test.ml -o dioph
 *)
open Dioph
let () =
  let open Z in
  let str_of_pair (x, y) = Format.sprintf "(%s, %s)" (to_string x) (to_string y) in
  let test_pqa p0 q0 d =
    let alphas, l = pqa (of_int p0) (of_int q0) (of_int d) in
    let alphas = String.concat " " (List.map to_string alphas) in
    Format.printf "%d %d %d -> %d (%s)\n" p0 q0 d l alphas
  in
  test_pqa 11 108 13;
  test_pqa 0 1 13;
  let test_pell1min d pos =
    let res = pell1_min (of_int d) pos in
    match res with
    | None -> assert false
    | Some (x, y) -> Format.printf "%d %d -> %s %s\n" d (if pos then 1 else -1) (to_string x) (to_string y)
  in
  test_pell1min 13 true;
  test_pell1min 13 false;
  let test_pell1 d pos =
    let res = pell1 (of_int d) pos (of_int 1000000) in
    let res = String.concat " " (List.map str_of_pair res) in
    Format.printf "%d %d -> %s\n" d (if pos then 1 else -1) res
  in
  test_pell1 13 true;
  test_pell1 13 false;
  let test_pell_funds_bf d n =
    let res = pell_funds_bf (of_int d) (of_int n) in
    let res = String.concat " " (List.map str_of_pair res) in
    Format.printf "Funds: %d %d -> %s\n" d n res
  in
  test_pell_funds_bf 13 108;
  test_pell_funds_bf 157 12;
  test_pell_funds_bf 13 27;
  let test_pell_bf d n max_x =
    let res = pell_bf (of_int d) (of_int n) (of_int max_x) in
    let res = String.concat " " (List.map str_of_pair res) in
    Format.printf "BF: %d %d -> %s\n" d n res
  in
  test_pell_bf 13 108 1000;
  test_pell_bf 157 12 100000000;
  test_pell_bf 13 27 1000
 
