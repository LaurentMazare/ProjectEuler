let cache = Hashtbl.create 4
let rec coll n =
  if n == 1 then 1
  else if Hashtbl.mem cache n then Hashtbl.find cache n
  else
    let res = 1 + coll (if n mod 2 == 0 then n/2 else 3*n+1) in
    Hashtbl.add cache n res;
    res

let rec foldi f acc lo up =
  if up < lo then acc else foldi f (f acc lo) (lo+1) up

let maxidx acc n =
  let coll = coll n in
  if snd acc < coll then (n, coll) else acc

let () = Format.printf "%d\n" (fst (foldi maxidx (0, 0) 1 1_000_000))
