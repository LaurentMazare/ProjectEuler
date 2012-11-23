from array import array
lim = 10 ** 5
max_l = lim * lim - 1
primes = []
factors = array('l', [0] * lim)
for n in xrange(2, lim):
  if factors[n] == 0:
    primes.append(n)
    nn = n
    while nn < lim:
      factors[nn] = n
      nn += n
print len(primes)

def s(prev_p, max_p, prod):
  total = 0 if prev_p else prod
  min_p = max(prev_p) if prev_p else 0
  for p in primes:
    if min_p > p: continue
    if p > max_p: break
    current_p = dict(prev_p)
    if p in prev_p:
      q = 3 if current_p[p] == 1 else 1
      del current_p[p]
    else: q = 2
    pminus = p - 1
    while pminus != 1:
      f = factors[pminus]
      nb = 0
      while pminus % f == 0:
        pminus /= f
        nb += 1
      if f in current_p:
        nb = (current_p[f] + nb) % 3
        if nb == 0: del current_p[f]
        else: current_p[f] = nb
      elif nb % 3 != 0: current_p[f] = nb % 3
    while True:
      pp = p ** q
      if pp * prod > max_l: break
      total += s(current_p, p-1, pp*prod)
      q += 3
  return total
print s({}, lim, 1) - 1

