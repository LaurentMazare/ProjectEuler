from math import log
def primes_sieve(max_p):
  max_p += 1
  factors = [0] * max_p
  for p in xrange(2, max_p):
    if factors[p] == 0:
      for j in xrange(p*2, max_p, p): factors[j] = p
  return factors
factors = primes_sieve(10**6)
print "Sieving done."

# For a prime number p, return the exponent of p in the prime
# decomposition of n!
def in_fact(p, n):
  pp = p
  res = 0
  while n / pp > 0:
    res += n / pp
    pp *= p
  return res

# For a prime number p, return the smallest n such that
# p^alpha divides n!
def smallest_n(p, alpha):
  lo = 1
  up = alpha
  while up - lo > 1:
    mid = (up + lo) / 2
    nb = in_fact(p, p*mid)
    if nb >= alpha: up = mid
    else: lo = mid
  if in_fact(p, lo*p) >= alpha: return lo*p
  return up*p

total = 0
m = 0 # This works as for 10!, the interesting power is on 5
for n in xrange(10, 10**6 + 1):
  if n % 1000 == 0: print n
  nn = n
  factors_of_n = []
  while factors[nn] != 0 and nn > 1:
    f = factors[nn]
    while nn % f == 0: nn /= f
    factors_of_n.append(f)
  if nn > 1: factors_of_n.append(nn)
  for f in factors_of_n:
    x = in_fact(f, n)
    sm = smallest_n(f, 1234567890*x)
    if sm > m:
      m = sm
  total += m
print total % 10**18
