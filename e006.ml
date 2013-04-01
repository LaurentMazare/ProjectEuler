let s1 n = (n*(n+1))/2
let s2 n = (n*(n+1)*(2*n+1))/6
let sqr x = x * x
let () = Format.printf "%d\n" (sqr (s1 100) - s2 100)
