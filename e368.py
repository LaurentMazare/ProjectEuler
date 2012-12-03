# This uses the algorithm described in Schmelzer and Baillie'08:
# Summing Currious, Slowly Convergent, Harmonic Subseries
import itertools
def fact(x): return 1 if x == 0 else x * fact(x-1)
def c(k, w): return fact(k+w-1)/(fact(w)*fact(k-1)) * (1 if w % 2 == 0 else -1)
cache_a = {}
def a(k, w, m):
  if not (k, w, m) in cache_a:
    cache_a[(k, w, m)] = c(k, w) * m ** w * 10 ** (-k-w)
  return cache_a[(k, w, m)]

# S_i^j is ending with j for 0 <= j < 10, and ending with (j-10)(j-10) for 10 <= j < 20
nn = 20
def t(l, m):
  if l < 10: return (m+10) if l == m else m
  return -1 if l == m+10 else m

cache = {}
def psi(i, j, k):
  if (i>1 and k>12) or (i>4 and k>5) or (i>10 and k>2): return 0
  global nn
  if (i, j, k) in cache: return cache[(i, j, k)]
  if i == 1: res = 0 if j == 0 or 10 <= j else j ** (-k)
  elif i == 2:
    if 11 <= j: res = (j-10 + 10*(j-10)) ** (-k)
    elif j < 10: res = sum([0 if jj == j else (jj*10+j)**(-k) for jj in xrange(1, 10)])
    else: res = 0
  else:
    res = 0
    for m, l in itertools.product(xrange(0, 10), xrange(0, nn)):
      if t(l, m) == j: res += sum([psi(i-1, l, k+w)*a(k, w, m) for w in xrange(0, 20)])
  cache[(i, j, k)] = res
  return res

print "%.10f\n" % sum([psi(i, j, 1) for i, j in itertools.product(xrange(1, 10000), xrange(0, nn))])
