def sd(n): # Sum of digits of n in basis 5
  return 0 if n == 0 else n % 5 + sd(n/5)

cache = {}
# Nb of integer n in [lo, up] such that sd(2n-1)-2sd(n)>=target
# n also has to be lower than 5**k
def t(k, lo, up, target):
  b = 5**k
  up = min(up, 5*b-1)
  if up < lo: return 0
  key = k, lo, up, target
  if key in cache: return cache[key]
  if k == 0:
    res = sum([lo <= a and a <= up and sd(2*a-1)-2*sd(a) >= target for a in xrange(1, 5)])
  else:
    res = t(k-1, lo, up, target)
    for a in xrange(1, 5):
      res += lo <= a*b and a*b <= up and sd(2*a*b-1)-2*sd(a*b)>=target
      res += t(k-1, max(1, lo-a*b), min(up-a*b, (b+1)/2), target+2*a-sd(2*a))
      res += t(k-1, max((b+1)/2, lo-a*b), up-a*b, target+2*a-sd(2*a+1)+1)
  cache[key] = res
  return res

print t(30, 1, 10**18, 0) # As f5(n!) = (n-sd(n)) / 4
