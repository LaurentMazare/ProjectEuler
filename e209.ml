let c l1 l2 = (* Cartesian product. *)
  List.fold_left (fun acc x -> List.fold_left (fun acc y -> (x, y)::acc) acc l2) [] l1

let fib n = (* Fibonacci sequence in linear time and constant memory. *)
  let rec aux prev_x x = function
    | 1 -> x
    | n -> aux x (x + prev_x) (n-1)
  in
  if n = 0 then 0 else aux 0 1 n
(* The number of cyclic sequence of length n with no two adjacent 1. *)
let cycle_configs n = if n = 1 then 1 else fib (n+1) + fib (n-1)

let next_state (a, b, c, d, e, f) = b, c, d, e, f, (a <> (b && c))
let flatten (a, (b, (c, (d, (e, f))))) = a, b, c, d, e, f

let () =
  let bi = [false; true] in
  let all_inputs = List.map flatten (c bi (c bi (c bi (c bi (c bi bi))))) in
  let nb_configs = (* Locate all the cycles. *)
    let nb_cycles (acc_states, nb) start_state =
      let rec aux hist steps state =
        if steps > 0 && state = start_state then hist, nb * cycle_configs steps
        else aux (state::hist) (steps+1) (next_state state)
      in
      if List.mem start_state acc_states then acc_states, nb
      else aux acc_states 0 start_state
    in
    snd (List.fold_left nb_cycles ([], 1) all_inputs)
  in
  Format.printf "%d\n" nb_configs
