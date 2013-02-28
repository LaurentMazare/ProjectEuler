# From http://oeis.org/A068920/a068920.txt, we can
# implement an inefficient algorithm allowing to discover
# the following patter: (x, y) with x < y cannot be tiled
# if both x and y are even or y is in:
# [x+2, 2x-4] U [2x+4, 3x-5] U [3x+5, 4x-6] U ...
def tilable(x, y):
  if (x*y) & 1 or y < x: return False
  p, q = divmod(y, x)
  if p + 2 <= q and q <= x - p - 3: return False
  return True

bound, primes, target = 10**9, [2, 3, 5, 7, 11, 13, 17, 19, 23], 200
all = []

def nb_free(idx, pdec, a, x):
  if idx == len(pdec):
    b = x / a
    if a != 1 and a < b and not tilable(a, b): return 1
    return 0
  total = 0
  p, q = pdec[idx]
  for i in xrange(0, q+1):
    total += nb_free(idx+1, pdec, a, x)
    a *= p
  return total

def walk(idx, prod, nb_factors, pdec):
  if idx == len(primes):
    if prod & 1 == 0 and 2*target <= nb_factors and nb_free(0, pdec, 1, prod) == target:
      all.append(prod)
    return
  p, prod_i = primes[idx], prod
  for i in xrange(0, 7):
    if bound < prod_i: break
    pdec.append((p, i))
    walk(idx+1, prod_i, nb_factors*(i+1), pdec)
    pdec.pop()
    prod_i *= p

walk(0, 1, 1, [])
print "Found %d numbers below %d, smallest: %d" % (len(all), bound, min(all))
