# DP solution based on the string length.
# For a given length, we output two set of configuration numbers. The first
# set is for strings that have no substring divisible by m, the second set
# is for strings that have one substring divisible by m.
# A configuration number is a mapping from some right-configuration array to
# the number of such configurations before 10^n.
# For example, for m = 4, mapping [0, 2, 1, 1] -> 3 means that we have found
# 3 strings such that:
#   0 of the right prefixes have sum 0 mod m
#   2 of the right prefixes have sum 1 mod m
#   1 of the right prefixes have sum 2 mod m
#   1 of the right prefixes have sum 4 mod m
def f(n, m):
  if n == 0:
    tag = tuple([0] * m)
    return ({tag: 1}, {tag: 0})
  # res0 contains configurations with 0 substring divisible by m
  # res1 contains configurations with 1 substring divisible by m
  res0, res1 = {}, {}
  old0, old1 = f(n-1, m)
  for k in xrange(int(n==1), 10):
    for config, nb in old0.iteritems():
      key = [0] * m
      key[k % m] = 1
      for i, j in enumerate(config):
        key[(10*i+k) % m] += j
      if key[0] >= 2: continue
      target = res1 if key[0] else res0
      key = 0 if n == m else tuple(key)
      target[key] = target.get(key, 0) + nb
    for config, nb in old1.iteritems():
      key = [0] * m
      key[k % m] = 1
      for i, j in enumerate(config):
        key[(10*i+k) % m] += j
      if key[0] >= 1: continue
      key = 0 if n == m else tuple(key)
      res1[key] = res1.get(key, 0) + nb
  return res0, res1

def F(n):
  return sum([sum(f(k, k)[1].values()) for k in xrange(1, n+1)])

print F(19)
