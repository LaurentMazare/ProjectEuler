cacheFixed = {}
# Numbers of way to split nbB blacks and nbW whites
# in packs of size size with at most maxW whites per pack.
# Note that nbB + nbW will always be divisible by size
def combFixed(nbB, nbW, size, maxW):
  key = (nbB, nbW, size, maxW)
  if maxW < 0 or nbB < 0 or nbW < 0 or maxW > size:
    return 0
  if nbB == 0 and nbW == 0:
    return 1
  if maxW == 0 and nbW == 0:
    return 1
  if cacheFixed.has_key(key):
    return cacheFixed[key]
  res = 0
  res += combFixed(nbB - (size - maxW), nbW - maxW, size, maxW)
  res += combFixed(nbB, nbW, size, maxW - 1)
  cacheFixed[key] = res
  return res

cache = {}
# Numbers of way to split nbB blacks and nbW whites in packs
# using only packs which size is between minS and maxS
def comb(nbB, nbW, minS, maxS):
  if nbB == 0 and nbW == 0:
    return 1
  if minS > nbB + nbW:
    return 0
  if minS == maxS:
    if (nbB + nbW) % maxS != 0:
      return 0
    return combFixed(nbB, nbW, minS, min(nbW, minS))
  key = (nbB, nbW, minS, maxS)
  if cache.has_key(key):
    return cache[key]
  res = 0
  mid = (minS + maxS) / 2
  for iB in xrange(0, nbB + 1):
    for iW in xrange(0, nbW + 1):
      c1 = comb(iB, iW, minS, mid)
      c2 = comb(nbB - iB, nbW - iW, mid + 1, maxS)
      res += c1 * c2
  cache[key] = res
  return res

print comb(3, 1, 1, 4)
print comb(60, 40, 1, 100)
