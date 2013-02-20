import itertools
def gcd(x, y): return x if y == 0 else gcd(y, x % y)

def f(max_s):
  res = 0
  for u in xrange(1, max_s/2):
    for v in xrange(1+u%2, u, 2):
      if gcd(u, v) != 1: continue # Yes, we should use a Stern-Brocot tree...
      b, d = u*u - v*v, 2*u*v
      if max_s <= b+d: break
      res += max_s / (b+d) * (1 if b == d else 2)
  for u in xrange(1, max_s, 2):
    for v in itertools.count(1):
      if gcd(u, v) != 1: continue # Yes, we should use a Stern-Brocot tree...
      a = u*u + 2*v*v
      b = 2*u*v + a
      if max_s/2 < b: break
      res += (max_s - 1) / (b + b)
  return res

print f(10**8)
