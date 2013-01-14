# Caution, this does not work for now
# It runs up to n = 5000 in ~30s on my Core2Duo @ 2.2GHz
# But complexity seems to be exponential :(
import sys
import array
sys.setrecursionlimit(100000)

def sieve(n):
  is_prime = [1] * (n+1)
  primes = []
  for i in xrange(2, n+1):
    if is_prime[i]:
      primes.append(i)
      j = i + i
      while j <= n:
        is_prime[j] = 0
        j += i
  return primes

lim = 5000
primes = array.array('l', sieve(lim))
nb_primes = len(primes)
print "Sieve done!"

def lim1(x):
  xx = 1
  while xx <= lim: xx *= x
  return xx / x

def lim2(x, y):
  res = 0
  xx = 1
  while xx <= lim:
    xy = xx
    while xy <= lim: xy *= y
    res = max(res, xy / y)
    xx *= x
  return res

lim1_a = array.array('l', [lim1(primes[x]) for x in xrange(0, nb_primes)])
print "Cache 1 filled!"

lim2_pairs = []
for idx1 in xrange(0, nb_primes):
  l1 = lim1_a[idx1]
  p1 = primes[idx1]
  tmp = {}
  for idx2 in xrange(0, idx1):
    p2 = primes[idx2]
    if p1 * p2 > lim: break
    l1_bis = lim1_a[idx2]
    l2 = lim2(p1, p2)
    if l2 > l1 + l1_bis: tmp[idx2] = l2
  lim2_pairs.append(tmp)
print "Cache 2 filled!"

cache = {}
def co_rec(prime_idx, already_in, acc_sum):
  if prime_idx < 0: return acc_sum
  if prime_idx in already_in: return co_rec(prime_idx-1, already_in, acc_sum)
  key = prime_idx
  for idx in already_in:
    if idx < prime_idx: key = (key, idx)
  if key in cache: return acc_sum + cache[key]
  p = primes[prime_idx]
  lim1 = lim1_a[prime_idx]
  current_m = co_rec(prime_idx-1, already_in, acc_sum + lim1)
  for (prime_idx2, lim2) in lim2_pairs[prime_idx].iteritems():
    p2 = primes[prime_idx2]
    if prime_idx2 in already_in: continue
    lim1_bis = lim1_a[prime_idx2]
    already_in.add(prime_idx2)
    current_m = max(current_m, co_rec(prime_idx-1, already_in, acc_sum + lim2))
    already_in.remove(prime_idx2)
  cache[key] = current_m - acc_sum
  return current_m
print 1+co_rec(nb_primes-1, set(), 0)
