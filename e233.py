# x^2+y^2 = n has 4*(d1+1)*(d2+1)*...*(dk+1) solutions
# if n = 2^u*p1^d1*...*pk^dk*q1^e1*...qi^ei where pi and qi are
# prime such that pi % 4 = 1 and qi % 4 = 3
# As 420 = 4*3*5*7, we have the following possibilities for
# d1,  d2, d3:
# 119  0   0
# 6    4   2
# 14   6
# 20   4
# 34   2
# Because of the limit to 10^11, N must have the form
# N = 2^u.p1^3.p2^2.p3.q1^e1...
# N = 2^u.p1^7.p2^3.q1^e1...
# N = 2^u.p1^10.p2^2.q1^e1...
# N = 2^u.p1^17.p2^1.q1^e1...
from array import array

def primes_sieve(max_p):
  max_p += 1
  primes1 = []
  no1 = []
  is_prime = array('b', [True] * max_p)
  contains1 = array('b', [False] * max_p)
  for p in xrange(2, max_p):
    if is_prime[p]:
      p_mod_4 = p % 4
      for j in xrange(p*2, max_p, p):
        is_prime[j] = False
        if p_mod_4 == 1: contains1[j] = True
      if p_mod_4 == 1:
        contains1[p] = True
        primes1.append(p)
    if not contains1[p]: no1.append(p)
  return primes1, no1
primes1, no1 = primes_sieve(5*10**6)
max_l = 10**11

def sums(p):
  res = p
  for q in no1:
    if p * q > max_l: break
    res += p * q
  return res

total = 0
for p1 in primes1:
  p1_3 = p1 ** 3
  if p1_3 > max_l: break
  for p2 in primes1:
    p1_3_p2_2 = p1_3 * p2 ** 2
    if p1_3_p2_2 > max_l: break
    if p1 == p2: continue
    for p3 in primes1:
      p = p1_3_p2_2 * p3
      if p > max_l: break
      if p1 == p3 or p2 == p3: continue
      total += sums(p)

for p1 in primes1:
  p1_7 = p1 ** 7
  if p1_7 > max_l: break
  for p2 in primes1:
    if p1 == p2: continue
    p = p1_7 * p2 ** 3
    if p > max_l: break
    total += sums(p)

for p1 in primes1:
  p1_10 = p1 ** 10
  if p1_10 > max_l: break
  for p2 in primes1:
    if p1 == p2: continue
    p = p1_10 * p2 ** 2
    if p > max_l: break
    total += sums(p)

print total
