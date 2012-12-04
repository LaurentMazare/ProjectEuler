import array

max_p = 10 ** 6
max_n = max_p ** 3
primes = []
factors = array.array('l', [0] * max_p)
for i in xrange(2, max_p): factors[i] = i
for i in xrange(2, max_p):
  if factors[i] == i:
    primes.append(i)
    j = i * 2
    while j < max_p:
      factors[j] = i
      j += i
primes = array.array('l', primes)
print "Sieving finished (%d primes)." % len(primes)

def gcd(x, y): return x if y == 0 else gcd(y, x % y)
def check_achille(factor_list):
  gg = None
  for q, n in factor_list:
    if n < 2: return False
    gg = n if gg == None else gcd(gg, n)
  return gg == 1

def check(factor_list):
  if not check_achille(factor_list): return False
  phi = {}
  for q, n in factor_list:
    phi[q] = phi.get(q, 0) + n - 1
    q_minus = q - 1
    while q_minus != 1:
      f = factors[q_minus]
      nb_f = 0
      while q_minus % f == 0:
        q_minus /= f
        nb_f += 1
      phi[f] = phi.get(f, 0) + nb_f
  return check_achille(list(phi.iteritems()))

def aux(max_q, acc, acc_l, first):
  global max_n
  if acc > max_n: return 0
  res = int(check(acc_l))
  for j in xrange(0, max_q):
    q = primes[j]
    nb_q = 3 if first else 2
    qq = q ** nb_q
    while acc * qq <= max_n:
      acc_l.append((q, nb_q))
      res += aux(j, acc * qq, acc_l, False)
      acc_l.pop()
      qq *= q
      nb_q += 1
  return res

print aux(len(primes), 1, [], True)
