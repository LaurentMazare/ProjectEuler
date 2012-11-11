from math import sqrt
def sum_sigma2_(n):
  return sum([i*i*(n/i) for i in xrange(1, n+1)])
def sum_squares(n):
  return (n * (n+1) * (2*n+1)) / 6
def sum_sigma2(n):
  total = 0
  n_inter = int(sqrt(n))
  for x in xrange(1, n_inter + 1):
    total += sum_squares(n / x)
  for x in xrange(1, n/n_inter + 1):
    total += x * x * max(0, n/x - n_inter)
  return total

print sum_sigma2(10 ** 15)
