from array import array
cache = {}
# Takes as input an array u_0, u_1,... such that there is u_k segments of length k
# Returns a structure {i: j} -> j possibilites to have a max of i segments
def comb(sizes):
  nb_segs = sum(sizes)
  if nb_segs == 1 and sizes[1] == 1: return {1: 1}
  key = str(sizes)
  if key in cache: return cache[key]
  res = {}
  for size, nb in enumerate(sizes):
    if nb == 0: continue
    sizes[size] -= 1
    if size == 1:
      tmp = comb(sizes)
      for s, nb_combs in tmp.iteritems():
        if s < nb_segs: res[nb_segs] = res.get(nb_segs, 0) + nb_combs * nb
        else: res[s] = res.get(s, 0) + nb_combs * nb
    else:
      for size_1 in xrange(0, size):
        size_2 = size - size_1 - 1
        if size_1 != 0: sizes[size_1] += 1
        if size_2 != 0: sizes[size_2] += 1
        tmp = comb(sizes)
        for s, nb_combs in tmp.iteritems():
          if s < nb_segs: res[nb_segs] = res.get(nb_segs, 0) + nb_combs * nb
          else: res[s] = res.get(s, 0) + nb_combs * nb
        if size_1 != 0: sizes[size_1] -= 1
        if size_2 != 0: sizes[size_2] -= 1
    sizes[size] += 1
  cache[key] = res
  return res

nb = 40
input = array('i', [0] * (nb+1))
input[nb] = 1
combs = comb(input)
total = sum(combs.values())
print "%.6f" % (sum([float(nb * m) for m, nb in combs.iteritems()]) / total)
