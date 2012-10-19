import itertools
lim = 10 ** 6
all_triangles = {}
for m in xrange(1, 1001):
  for n in xrange(1, m):
    a = m*m - n*n
    b = 2 * m * n
    c = m*m + n*n
    if c >= lim: break
    k = 1
    while True:
      if k*c >= lim: break
      if not k*a in all_triangles: all_triangles[k*a] = set()
      if not k*b in all_triangles: all_triangles[k*b] = set()
      all_triangles[k*a].add(k*b)
      all_triangles[k*b].add(k*a)
      k += 1
total = 0
for w, heights in all_triangles.iteritems():
  for h1, h2 in itertools.combinations(heights, 2):
    if (h1 * h2) % (h1 + h2) == 0: total += 1
print total
