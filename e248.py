def fact(x): return 1 if x == 1 else x * fact(x-1)
fact13 = fact(13)
from math import log

# Deterministic Miller-Rabin
def isprime(n):
  if n == 2: return True
  if n % 2 == 0: return False
  if n == 6227020801: return False
  assert 1 < n < 4759123141 and n % 2 != 0, n
  s = 0
  d = n-1
  while d & 1 == 0:
    s += 1
    d >>= 1
  assert d % 2 != 0 and (n-1) == d*2**s
  for a in [2, 7, 61]:
    if not 2 <= a <= min(n-1, int(2*log(n)**2)):
      break
    if (pow(a, d, n) != 1 and all(pow(a, d*2**r, n) != (n-1) for r in xrange(s))):
      return False
  return True

factors = []     # All factors n of 13! such that n+1 is prime
all_factors = [] # All factors of n
for p2 in xrange(0, 11):
  for p3 in xrange(0, 6):
    for p5 in xrange(0, 3):
      for p7 in xrange(0, 2):
        for p11 in xrange(0, 2):
          for p13 in xrange(0, 2):
            n = 2 ** p2 * 3 ** p3 * 5 ** p5 * 7 ** p7 * 11 ** p11 * 13 ** p13
            all_factors.append(n)
            if isprime(n+1) and n != 1:
              factors.append(n)

cache = {}
# Generate all the possible factorization of x with factors greater than min_x
def f(min_x, x):
  if x == 1: return [[]]
  key = (min_x, x)
  if key in cache: return cache[key]
  res = []
  for i in factors:
    if i <= min_x: continue
    if x % i == 0:
      tmp = f(i, x / i)
      for l in tmp:
        res.append(l + [i])
  cache[key] = res
  return res

res = []
for base in all_factors:
  tmp = f(0, base)
  for t_ in tmp:
    remainder = fact13 / base
    v = 1
    for t in t_:
      p = t + 1
      k = 1
      while remainder % p == 0:
        remainder /= p
        k += 1
      v *= p ** k
    if remainder == 1:
      res.append(v)
      res.append(2*v)
    elif remainder % 2 == 0:
      k = 1
      while remainder % 2 == 0:
        remainder /= 2
        k += 1
      v *= 2 ** k
      if remainder == 1:
        res.append(v)
res.sort()

print len(res), res[150000 - 1]
