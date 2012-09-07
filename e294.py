import itertools

def pow_10(n):
  if n == 0: return 1
  if n % 2 == 0:
    tmp = pow_10(n/2)
    return (tmp * tmp) % 23
  return (10 * pow_10(n-1)) % 23

cache = {}
# Number of integer x with specified nb of digits such that
# sum_digits(x) == sum_digits and x % 23 == mod23
# Implemented as a fast exponentiation to make it quicker
def s(sum_digits, mod23, digits):
  if digits == 1: return 1 if sum_digits == mod23 and sum_digits < 10 else 0
  key = (sum_digits, mod23, digits)
  if key in cache: return cache[key]
  if digits % 2 == 0:
    res = 0
    p = pow_10(digits/2)
    for m1, m2 in itertools.product(xrange(0, 23), xrange(0, 23)):
      if (m1 * p + m2) % 23 == mod23:
        for sd in xrange(0, sum_digits+1):
          res += s(sd, m1, digits/2) * s(sum_digits - sd, m2, digits/2)
  else:
    res = 0
    for x, m in itertools.product(xrange(0, min(10, sum_digits+1)), xrange(0, 23)):
      if (x + 10 * m) % 23 == mod23:
        res += s(sum_digits - x, m, digits - 1)
  res = res % (10 ** 9)
  cache[key] = res
  return res

print s(0, 0, 5)
print s(23, 0, 4)
print s(23, 0, 9)
print s(23, 0, 42)
print s(23, 0, 11 ** 12)
