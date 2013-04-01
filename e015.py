def fact(x): return 1 if x == 0 else x * fact(x-1)
def c(n, p): return fact(n)/fact(p)/fact(n-p)
print c(40, 20)
