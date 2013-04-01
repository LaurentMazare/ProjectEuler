def fact(x): return 1 if x == 0 else x * fact (x-1)
print sum([int(c) for c in str(fact(100))])
