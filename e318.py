# Just note that (sqrt(p)+sqrt(q))^(2n)+(sqrt(p)-sqrt(q))^(2n)
# is an integer
from math import *
res = 0
for p in xrange(1, 2011 / 2 + 1):
  sqrt_p = sqrt(p)
  for q in xrange(p+1, int((1+sqrt_p)**2) + 1):
    if p + q > 2011: break
    x = (sqrt_p - sqrt(q)) ** 2
    if x < 1: res += int(0.5 + ceil(-2011*log(10)/log(x)))
print res

