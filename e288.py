def N(p, n, m):
  res = 0
  s = 290797
  p_to = [p ** u for u in xrange(0, m+1)]
  for k in xrange(1, n+1):
    s = (s * s) % 50515093
    t = s % p
    res += sum([t * p_to[u] for u in xrange(0, min(k, m))])
    res %= p_to[m]
  return res

print N(3, 10 ** 4, 20)
print N(61, 10 ** 7, 10)
