from sets import *
cache_p = {}
not_prime = Set()
lim = 100000
for i in range(2, lim):
  if i not in not_prime:
    j = 2
    while True:
      index = j * i
      if index >= lim:
        break
      not_prime.add(index)
      j+=1
primes = []
for i in range(2, lim):
  if i not in not_prime:
    primes.append(i)

def is_prime(n):
  if n == 1 or n == 0:
    return 0
  else:
    if n < lim:
      return n not in not_prime
    if cache_p.has_key(n):
      return cache_p[n]
    res = 1
    up = int(n**0.5)+1
    for x in primes:
      if n%x == 0:
        res = 0
        break
      if x > up:
        break
    cache_p[n] = res
    return res

cache_n = {}
def nb(current, first_digit, digits):
  is_p = is_prime(current)
  if len(digits) == 0:
    return is_p
  key = (current, first_digit, str(digits))
  if cache_n.has_key(key):
    return cache_n[key]
  res = 0
  for digit in digits:
    digits2 = digits[:] #list copy
    digits2.remove(digit)
    if is_p and digit > first_digit:
      res += nb(digit, digit, digits2)
    if current == 0:
      first_digit = digit
    res += nb(current * 10 + digit, first_digit, digits2)
  cache_n[key] = res
  return res

res = nb(0, 0, range(1, 10))
print res
