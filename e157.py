# Very brute force way to compute the number of factors
# but still the overall runs in less than 2 seconds so no need
# for optimization for now.
def nb_factors(x):
  res = 0
  for i in xrange(1, x + 1):
    i2 = i * i
    if i2 > x: break
    elif i2 == x: res += 1
    elif x % i == 0: res += 1
  return res

def gcd(a, b):
  if b == 0: return a
  else: return gcd(b, a % b)

def nb_sols(n):
  max_f = 10 ** n
  max_f2 = max_f * max_f
  res = 0
  for x in xrange(0, 2 * n + 1):
    for y in xrange(0, 2 * n + 1):
      f = 2 ** x * 5 ** y
      if f > max_f: break
      pa = max_f + f
      pb = max_f + max_f2 / f
      res += nb_factors(gcd(pa, pb))
  return res

print sum([nb_sols(i) for i in xrange(1, 10)])
