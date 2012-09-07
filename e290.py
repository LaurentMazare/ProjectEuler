def sum_digits(x):
  res = 0
  while x > 0:
    res += x % 10
    x /= 10
  return res

cache = {}
# Returns the number of integer with a specified numbof digits such that:
# sum_digits(137*x+alpha) = sum_digits(x) + beta
def nb(digits, alpha, beta):
  key = (digits, alpha, beta)
  if key in cache: return cache[key]
  if digits == 1:
    res = 0
    for x in xrange(0, 10):
      res += 1 if sum_digits(137*x + alpha) == sum_digits(x) + beta else 0
  else:
    res = 0
    for x in xrange(0, 10):
      alpha_b = (137 * x + alpha) / 10
      beta_b = beta + x - (137 * x + alpha) % 10
      res += nb(digits - 1, alpha_b, beta_b)
  cache[key] = res
  return res

print nb(18, 0, 0)

    
