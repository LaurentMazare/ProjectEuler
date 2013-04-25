# This is equivalent to m.n^2 + m.(m+1).n = k^2.(m+1) + m.(m+1).k
# And also to: m(2n+m+1)^2 - (m+1)(2k-m)^2 = m(m+1)
# However because of sqrt precision issue on float (and also to speed up processing),
# we simplify again the equation by noting that m divides k^2 so sqrt_(m) divides k
# where sqrt_(p1^q1...pn^qn) = p1^((1+q1)/2)...pn^((1+qn)/2)
# m(2n+m+1)^2/s_m - (m+1)(2k-m)^2.s_m = m(m+1)/s_m where s_m = sqrt_(m)
# Then we iterate over m and solve the equation as a variation of Pell equation
# using the algorithms implemented in dioph.py.
import dioph
from math import sqrt
max_k = 10**10
max_m = int(sqrt(max_k/2)+1)

factors = [0] * (1+max_m)
for i in xrange(2, 1+max_m):
  if factors[i] == 0:
    j = i
    while j <= max_m: factors[j], j = i, j+i

def sqrt_(x):
  res = 1
  while x != 1:
    f, nb_f = factors[x], 0
    while x % f == 0: x, nb_f = x / f, nb_f + 1
    res *= pow(f, (nb_f+1)/2)
  return res

pivots = set()
for m in xrange(1, max_m+1):
  s_m = sqrt_(m)
  s = dioph.quad_s(m/s_m, (m+1)*s_m, m/s_m*(m+1), 10**20)
  for x, y in s:
    two_n, two_k = x - m - 1, y + m/s_m
    if two_k % 2 == 0 and two_n % 2 == 0:
      n, k = two_n / 2, s_m * two_k / 2
      if k <= n and k <= max_k:
        pivots.add(k)
print sum(pivots)
