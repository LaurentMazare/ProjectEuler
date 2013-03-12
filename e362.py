from math import sqrt
max_n = 10 ** 10

# Compute the Mobius function using a sieve
up_n = int(sqrt(max_n+1)) + 1
factors, mu = [1] * up_n, [1] * up_n
for p in xrange(2, up_n):
  original_p = p
  if factors[p] == 1:
    pp = p
    while pp < up_n: factors[pp], pp = p, pp+p
  mob = 1
  while p != 1:
    f, nb_f = factors[p], 0
    while p % f == 0: p, nb_f = p / f, nb_f + 1
    if nb_f >= 2: mob = 0
    if nb_f & 1: mob = - mob
  mu[original_p] = mob

def sf(n): # Square free numbers between 2 and n (inclusive)
  return sum([mu[k]*(n/(k*k)) for k in xrange(1, 1+int(sqrt(n)))])-1

cache = {}
def s_rec(m, n): # Number of square free products below n with all factors >= m
  if n < m: return 0
  if (m, n) in cache: return cache[(m, n)]
  res = sf(n)-sf(m-1)
  res += sum([0 if mu[k] == 0 else s_rec(k, n/k) for k in xrange(m, 1+int(sqrt(n+1)))])
  cache[(m, n)] = res
  return res

def s(n):
  res = sf(n)
  res += sum([0 if mu[k] == 0 else s_rec(k, n/k) for k in xrange(2, 1+int(sqrt(n+1)))])
  return res

print s(max_n)
