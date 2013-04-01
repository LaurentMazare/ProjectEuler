def length(n) :
  for x in range(2,n+2):
    if pow(10, x, n) == 10: return x
print max([(length(n), n) for n in xrange(2, 1000)])[0]
