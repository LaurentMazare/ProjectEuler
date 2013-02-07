from math import sin, pi
def t(m, n): # OEIS 11649
  res, e = 1.0, 0
  for k in xrange(1, n):
    for h in xrange(1, m):
      res *= 4*sin(h*pi/(2*m))**2 + 4*sin(k*pi/(2*n))**2
      while res >= 10.0:
        res /= 10.0
        e += 1
  return res, e

print "%.4fe%d" % t(500, 100)
