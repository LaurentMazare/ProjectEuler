def succ(u, alpha):
  s = []
  for i in xrange(0, 5):
    u, x = divmod(u, alpha)
    s.append(x)
  s.sort()
  x, y = 0, 0
  for d in s: x = alpha * x + d
  for d in reversed(s): y = alpha * y + d
  return y - x

cache_d = {}
def dis(u, alpha):
  v = succ(u, alpha)
  if u in cache_d: return cache_d[u]
  res = 0 if v == u or v == 0 else 1 + dis(v, alpha)
  cache_d[u] = res
  return res

# Numbers of 5 digits nb such that a1-a5 = x and a2 - a4 = y
# Very reduced version after looking at all the possible equalities
def nb(x, y, alpha):
  if y == 0:
    return (alpha-x) * (10 + max(0, x-1) * 20)
  elif x == y:
    return (alpha-x)*(20 + (y-1) * 30)
  return (alpha-x)*(100 + 120*(y-1) + 120*y*(x-y-1))

def s(alpha):
  cache_d.clear()
  total, c1, c2 = 0, alpha**4 - 1, alpha**3 - alpha
  for x in xrange(1, alpha):
    total += sum([(1+dis(c1*x+c2*y, alpha))*nb(x, y, alpha) for y in xrange(0, 1+x)])
  return total-1

print s(15), s(111)
print sum([s(6*k+3) for k in xrange(2, 301)])
