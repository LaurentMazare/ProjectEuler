import itertools
from fractions import Fraction
cache = {}
def reachable(args):
  start, stop = args
  if cache.has_key(args):
    return cache[args]
  n = 0
  for x in xrange(start, stop+1):
    n = n * 10 + x
  s = set([Fraction(n, 1)])
  for i in xrange(start, stop):
    s1 = reachable((start, i))
    s2 = reachable((i+1, stop))
    for x1, x2 in itertools.product(s1, s2):
      s.add(x1 + x2)
      s.add(x1 - x2)
      s.add(x1 * x2)
      if x2 != 0:
        s.add(x1 / x2)
  cache[args] = s
  return s

r = reachable((1, 9))
res = 0
for x in r:
  if x.denominator == 1 and x.numerator > 0:
    res += x.numerator
print len(r), res
