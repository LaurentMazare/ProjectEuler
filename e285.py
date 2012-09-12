from math import sqrt, atan

# integral between lo and up of sqrt(r*r - x*x)
def int(r, lo, up):
  r2 = r * r
  f = lambda x: 0.5 * (x * sqrt(r2 - x*x) + r2 * atan(x / sqrt(r2 - x*x)))
  return f(up) - f(lo)

def p(k):
  if k == 1:
    h = sqrt(5.0) / 2.0
    res = int(1.5, 1.0, h) - (h - 1.0)
  else:
    k = float(k)
    k2 = k * k
    h1 = sqrt((k + 0.5) ** 2 - 1.0)
    h2 = sqrt((k - 0.5) ** 2 - 1.0)
    res = int(k + 0.5, 1, h1) - int(k - 0.5, 1, h2)
    res = (res - (h1 - h2)) / k2
  return res

print "%.5f" % sum(k * p(k) for k in xrange(1, 10**5 + 1))
