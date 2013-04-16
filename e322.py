# C(n, p) is divisible by a prime k if and only if there is at least
# one carry when adding p to n-p in basis k.
# The main issue is that 10 is not prime...
def aux(n, max_p, prefix, original_n, basis):
  if n == 0:
    if original_n == 0: return 1+max_p
    # If original is not zero, we also have to remove the binomial that can be divided by 2
    # This is done in a very brute force way and should definitely be optimized...
    p, b = 0, 1
    for d in reversed(prefix): p, b = basis*p + d, b*basis
    res = sum([int(0 == original_n & (x * b + p)) for x in xrange(0, 1+max_p)])
    return res
  digit = n % basis
  res = 0
  for d in xrange(0, basis):
    if max_p < d: break
    if digit + d < basis:
      prefix.append(d)
      res += aux(n/basis, (max_p-d) / basis, prefix, original_n, basis)
      prefix.pop()
  return res

# Returns the total nb of binomial minus the ones that cannot be divided by 2
# minus the ones that cannot be divided by 5 + the ones that cannot be divided by
# 2 nor 5.
def fast_t(m, n):
  return m-n-aux(n, m-n-1, [], 0, 5) - aux(n, m-n-1, [], 0, 2) + aux(n, m-n-1, [], n, 5)

print fast_t(10**18, 10**12-10)
