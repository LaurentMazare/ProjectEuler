def ab_mod(idx, mod):
  idx = mod + (idx - mod) % (mod * mod - mod) # mod*mod - mod periodicity after the first mod elements
  facts, ifacts = [1], [1]
  for n in xrange(1, mod):
    f = (facts[-1] * n) % mod
    facts.append(f)
    ifacts.append(pow(f, mod-2, mod)) # Use Fermat's theorem for inversion instead of Bezout
  n, a, b = 0, [1], [-1]
  while True:
    if n == idx: return (a[n] + b[n]) % mod
    n += 1
    tmp_a, tmp_b = (0, 0) if mod <= n else (facts[n], -facts[n])
    ff = 1
    for i in xrange(0, n):
      c, nn, mm = 1, n, i # Use Lucas' theorem to compute c=binomial(n, i) % mod
      while mm > 0 and c > 0:
        (nn, nn_mod), (mm, mm_mod) = divmod(nn, mod), divmod(mm, mod)
        c = 0 if nn_mod < mm_mod else (c*facts[nn_mod]*ifacts[mm_mod]*ifacts[nn_mod-mm_mod]) % mod
      tmp_a, tmp_b = (tmp_a + a[i]*c) % mod, (tmp_b +b[i]*c - ff) % mod
      ff = (ff * (n-i)) % mod
    a.append(tmp_a)
    b.append(tmp_b)

factors = [7, 11, 73, 101, 137]
prod = reduce(lambda x, y: x*y, factors, 1)
mods = [(p, ab_mod(10**9, p)) for p in factors]
# Brute force Chinese Remainder Theorem solving :)
for n in xrange(0, prod):
  ok = True
  for p, m in mods:
    if n % p != m:
      ok = False
      break
  if ok:
    print n
    break
