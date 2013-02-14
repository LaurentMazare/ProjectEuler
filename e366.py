# This first part of the code has been used to compute the values of m
# for n between 1 and 1000 and spot the pattern in it.
# Complexity is O(n^2)
cache = {}
def win(n, k): # n stones, pick up a maximum of k
  if k >= n: return True
  if (n, k) in cache: return cache[(n, k)]
  res = False
  for taken in xrange(1, 1+min(k, n)):
    if not win(n-taken, 2*taken):
      res = True
      break
  cache[(n, k)] = res
  return res

def m(n):
  return max([t if not win(n-t, 2*t) else 0 for t in xrange(1, 2+n/3)])

print sum([m(n) for n in xrange(1, 101)])

def fib2(n):
  fibs, res = [0, 1], []
  for i in xrange(1, n):
    fibs.append(fibs[-1] + fibs[-2])
    res.append((fibs[-1]-1) / 2)
  return res

def sum_int(n, m):
  return (n*(n+1)) / 2 - (m*(m+1)) / 2

def sum_m(n):
  u = fib2(100) # This should be enough up to 10^22
  idx, f_idx, s, f_indexes = 1, 0, 0, []
  while True:
    u_idx = u[f_idx]
    if n < idx + u_idx: # Assume this is the only possible exit point
      return s + sum_int(n-idx, 0)
    s += sum_int(u_idx, 0)
    idx += u_idx + 1
    if (f_idx % 2 == 0 and 2 < f_idx): f_indexes.append(1)
    for i, fi in enumerate(f_indexes):
      s += sum_int(u[fi+1], u[fi])
      idx += u[fi+1] - u[fi]
      f_indexes[i] += 1
    f_idx += 1
  return s
print sum_m(10**18) % (10 ** 8)
