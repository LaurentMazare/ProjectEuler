from fractions import Fraction

def isprime(n):
  if n < 2:
    return False
  if n == 2:
    return True
  if not n & 1:
    return False
  for x in range(3, int(n**0.5)+1, 2):
    if n % x == 0:
      return False
  return True
primes = {}
def memo_prime(n):
  if primes.has_key(n):
    return primes[n]
  primes[n] = isprime(n)
  return primes[n]

cache = {}
def f(i, s):
  if cache.has_key((i,s)):
    return cache[(i,s)]
  if s[0] == 'P':
    if memo_prime(i):
      p = Fraction(2,3)
    else:
      p = Fraction(1,3)
  if s[0] == 'N':
    if memo_prime(i):
      p = Fraction(1,3)
    else:
      p = Fraction(2,3)
  if len(s) == 1:
    res = p
  else:
    ss = s[1:]
    if i == 1:
      res = f(2, ss)
    elif i == 500:
      res = f(499, ss)
    else:
      res = f(i-1, ss) / 2 + f(i+1, ss) / 2
    res = p * res
  cache[(i, s)] = res
  return res

print sum([f(i, "PPPPNNPPPNPPNPN") / 500 for i in xrange(1, 501)])
