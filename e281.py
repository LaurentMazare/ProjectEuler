def fact(x):
  res = 1
  for i in xrange(1, x+1): res *= i
  return res
def chooses(n, p): return fact(n) / (fact(p) * fact(n-p))

def f(m, n):
  combs = {}
  total = 0
  # compute f(m, n) by adding all the possibilities periodical
  # of period k * m for any k between 1 and n
  for k in xrange(1, n+1):
    if n % k != 0: continue
    tmp = 1
    for i in xrange(0, m-1): tmp *= chooses(k*(m-i) - 1, k)
    tmp -= sum([combs[i] if k % i == 0 else 0 for i in xrange(1, k)])
    combs[k] = tmp
    total += tmp / k
  return total

max_l = 10 ** 15
total = 0
for m in xrange(2, 200):
  if f(m, 1) > max_l: break
  for n in xrange(1, 100):
    combs = f(m, n)
    if combs > max_l: break
    total += combs
print total
