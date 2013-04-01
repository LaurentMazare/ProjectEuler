from math import sqrt
cache = {}
def sdivs(n):
  if not n in cache:
    cache[n] = 1+sum([d + n/d if n % d == 0 else 0 for d in xrange(2, 1+int(sqrt(n)))])
  return cache[n]
print sum([n if sdivs(sdivs(n)) == n and sdivs(n) != n else 0 for n in xrange(1, 10001)])
