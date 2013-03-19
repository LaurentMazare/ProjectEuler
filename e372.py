from decimal import *

# The algorithm below computes the number of points (x, y) in the right
# triangle a.x + b.y <= c, x > 0, y > 0
# A Simple Algorithm for Lattice Point Counting in Rational Polygons
# Hiroki Yanagisawa - IBM Research Report 2005
def calcN(a, b, c):
  m = c / a
  if a == b: return (m * (m-1)) / 2
  k, h = (a - 1) / b, (c - a*m) / b
  return calcN(b, a-b*k, c-b*(k*m+h)) + k*(m*(m-1))/2 + m*h

# Number of lattice points (x, y) in [M+1, N]^2 such that k <= (y*y)/(x*x)
def calcT(k, M, N):
  s, q = Decimal(k).sqrt(), 10**30
  p = int(s * q)
  if N*q - M*p <= 0: return 0
  return calcN(p, q, N*q - M*p) + (N*q) / p - M # As the line with y = 0 is not included in calcN
def calcRay(k, M, N): return calcT(2*k+1, M, N) - calcT(2*k+2, M, N)

M, N = 2*10**6, 10**9
print sum([calcRay(k, M, N) for k in xrange(0, (N*N)/(M*M)+1)])
