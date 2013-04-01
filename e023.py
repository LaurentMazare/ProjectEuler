import itertools
from math import sqrt
def sdivs(n):
  return 1+sum([d if d == n/d else d + n/d for d in xrange(2, 1+int(sqrt(n))) if n % d == 0])
maxp = 28123
abundants = [n for n in xrange(2, 28123) if n < sdivs(n)]
is_sum = [False] * maxp
for ab1, ab2 in itertools.combinations_with_replacement(abundants, 2):
  if ab1 + ab2 < maxp: is_sum[ab1+ab2] = True
print sum([n for n, s in enumerate(is_sum) if not s])
