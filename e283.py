from math import sqrt
def gcd(x, y): return x if y == 0 else gcd(y, x % y)

max_p = 2 * 10 ** 7
factors = [i for i in xrange(0, max_p)]
for p in xrange(2, max_p):
  if factors[p] == p:
    pp = p
    while pp < max_p:
      factors[pp] = p
      pp += p
print "Sieve done!"

def factorize(p):
  res = {}
  while p != 1:
    f = factors[p]
    nb_f = 0
    while p % f == 0:
      p /= f
      nb_f += 1
    res[f] = nb_f
  return res

def mult(d1, d2):
  res = dict(d2)
  for p, q in d1.iteritems(): res[p] = res.get(p, 0) + q
  return res

# From Lubomir Markov 2007: Heronian Triangles Whose Areas Are Integer
# Multiples Of Their Perimeters
def walk_rec(f_lhs, idx, delta1, delta2, m, u, v, max_delta1, inc):
  if delta1 > max_delta1: return 0
  res = 0
  if inc and (delta1 + 2*m*u) % v == 0 and (delta2 + 2*m*u) % v == 0:
    a = (delta1 + 2*m*u) / v + (2*m*v) / u
    b = (delta2 + 2*m*u) / v + (2*m*v) / u
    c = (delta1 + delta2 + 4*m*u) / v
    if b <= c: res += a + b + c
  if idx < len(f_lhs):
    p, q = f_lhs[idx]
    for q1 in xrange(0, q+1):
      res += walk_rec(f_lhs, idx+1, delta1, delta2, m, u, v, max_delta1, q1 > 0)
      delta1 *= p
      delta2 /= p
  return res

def sum_p(m):
  res = 0
  f_m = factorize(m)
  f_4m2 = mult({2: 2}, mult(f_m, f_m))
  for u in xrange(1, 2*m + 1):
    if (2*m) % u != 0: continue
    for v in xrange(1, 1+int(0.5+sqrt(3)*u)):
      if gcd(u, v) != 1: continue
      u2_plus_v2 = u*u + v*v
      f_lhs = mult(f_4m2, factorize(u2_plus_v2))
      f_lhs = list(f_lhs.iteritems())
      lhs = 4*m*m*u2_plus_v2
      max_delta1 = int(0.5 + 2*m*sqrt(u2_plus_v2))
      res += walk_rec(f_lhs, 0, 1, lhs, m, u, v, max_delta1, True)
  return res

print sum([sum_p(m) for m in xrange(1, 1001)])
