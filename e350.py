mod, maxD = pow(101, 4), 10**6 + 1
factors = [0] * maxD
for n in xrange(2, maxD):
  if factors[n] == 0:
    nn = n
    while nn < maxD:
      factors[nn] = n
      nn += n

cache_d = {}
def divs(n):
  if n == 0: return []
  elif n == 1: return [1]
  key = n
  if key in cache_d: return cache_d[key]
  f, nb_f = factors[n], 0
  while n % f == 0: n, nb_f = n/f, nb_f+1
  res = []
  for d in divs(n):
    for k in xrange(0, nb_f+1):
      res.append(d * f ** k)
  cache_d[key] = res
  return res

cache = {}
# ff returns the number of list of n integers of gcd 1 and lcm l
def ff(l, n):
  if 1 == l: return 1
  key = l, n
  if key in cache: return cache[key]
  div_list = divs(l)
  res = pow(len(div_list), n, mod)
  for d1 in div_list:
    d2 = d1
    for d2 in div_list:
      if d1 == 1 and d2 == l: continue
      if d1 <= d2 and d2 % d1 == 0:
        res -= ff(d2 / d1, n)
  res = res % mod
  cache[key] = res
  return res

# Main function, loops over the ratio lcm/gcd
def f(g, l, n):
  total = 0
  for g_over_l in xrange(1, 1+l/g):
    tmp = ff(g_over_l, n) * (l / g_over_l - g + 1)
    total = (total + tmp) % mod
  return total

print f(10, 100, 1)
print f(10, 100, 2)
print f(10, 100, 3)
print f(10, 100, 1000)
print f(10**6, 10**12, 10**18)
