# Generate all partitions for a set
def partitions(set_):
  if not set_:
    yield []
    return
  for i in xrange(2**len(set_)/2):
    parts = [set(), set()]
    for item in set_:
      parts[i&1].add(item)
      i >>= 1
    for b in partitions(parts[1]):
      yield [parts[0]]+b

# From the edges, compute the number of color map for one pattern
def basis(edges, nb_colors):
  nb = 0
  for p in partitions(range(1, 8)):
    ok = True
    for (x, y) in edges:
      for subset in p:
        if x in subset and y in subset:
          ok = False
          break
      if not ok:
        break
    if ok and len(p) <= nb_colors:
      comb = 1
      for i in xrange(0, len(p)):
        comb *= nb_colors - i
      nb += comb
  return nb

# Do it for A and B
nb_colors = 1984
nb1 = basis([ (1, 2), (1, 3), (2, 3), (3, 4), (4, 5), (5, 6), (5, 7), (6, 7), (1, 6), (2, 7) ], nb_colors)
nb2 = basis([ (1, 2), (1, 3), (2, 3), (3, 4), (4, 5), (5, 6), (5, 7), (1, 6), (2, 7) ], nb_colors)
print (nb1, nb2)

# Combine them in a recursive way
cache = {}
def combine(first, nbA, nbB):
  if nbA == 0 and nbB == 0:
    return 1
  key = (first, nbA, nbB)
  if cache.has_key(key):
    return cache[key]
  res = 0
  adj = 1 if first else nb_colors * (nb_colors-1)
  if nbA > 0:
    res += combine(False, nbA-1, nbB) * nb1 / adj
  if nbB > 0:
    res += combine(False, nbA, nbB-1) * nb2 / adj
  cache[key] = res
  return res

print combine(True, 25, 75)