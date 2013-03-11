from math import sqrt
def fact(n): return 1 if n == 0 else n * fact(n-1)
def ifact(n):
  res = {}
  for i in xrange(1, n+1):
    p = 2
    while True:
      if i == 1: break
      while i % p == 0:
        i /= p
        res[p] = res.get(p, 0) + 1
      p += 1
  return res

def walk(factors, lbound, ubound, current, index):
  if ubound < current: return []
  if len(factors) <= index: return [current] if lbound <= current else []
  res = []
  p, q = factors[index]
  pp = 1
  for qq in xrange(0, q+1):
    res += walk(factors, lbound, ubound, current * pp, index+1)
    pp *= p
  return res

target = 43
targetf = fact(target)
low_b, up_b = 0.99 * pow(targetf, 1/3.0), 1.01 * pow(targetf, 1/3.0)
factors = list(ifact(target).iteritems())
divs = walk(factors, low_b, up_b, 1, 0)
divs.sort()
lo, up = 0, len(divs)
while 1 + lo < up:
  mid = (lo + up) / 2
  d = divs[mid]
  if targetf > d*d*d: lo = mid
  else: up = mid
idx_a = up
c_over_a, where = None, None
while idx_a >= 0:
  a = divs[idx_a]
  idx_b = idx_a
  min_c = int(sqrt(targetf/a))
  if c_over_a != None and c_over_a < float(min_c) / float(a): break
  while True:
    b = divs[idx_b]
    if a*b*b > targetf: break
    if targetf % (a*b) == 0:
      c = targetf / (a*b)
      ca = float(c) / float(a)
      if c_over_a == None or ca < c_over_a:
        c_over_a, where = ca, (a, b, c)
    idx_b += 1
  idx_a -= 1
print where, sum(where)
