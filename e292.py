from math import sqrt

max_p = 120
vects = set([(0, -1, 1)]) # Set of vectors (x, y, norm)
# Add Pythagorean triples
for m in xrange(1, int(sqrt(max_p))):
  for n in xrange(1, m):
    a, b, c = m*m-n*n, 2*m*n, m*m+n*n
    k = 1
    while True:
      aa, bb, cc = k*a, k*b, k*c
      if max_p / 2 < cc: break
      for u, v in [(aa, bb), (bb, aa)]:
        for m_u, m_v in [(1, 1), (1, -1), (-1, 1), (-1, -1)]:
          vects.add((m_u * u, m_v * v, cc))
      k += 1
for m in xrange(1, 1+max_p/2):
  vects |= set([(m, 0, m), (0, m, m), (-m, 0, m)])
print "Vectors: ", len(vects)

def lower(dx1, dy1, dx2, dy2):
  if dx1 == 0 and dx2 == 0: return 0 < dy2 and dy1 < 0
  if dx1 == 0: return dy1 < 0 or dx2 < 0
  if dx2 == 0: return 0 < dx1 and 0 < dy2
  if 0 < dx1 and dx2 < 0: return True
  if dx1 < 0 and 0 < dx2: return False
  return dy1 * dx2 < dy2 * dx1

def aligned(dx1, dy1, dx2, dy2):
  return dx1 * dy2 == dy1 * dx2

v_sel = {}
for (dx, dy, _) in vects:
  f = lambda (a, b, _): lower(dx, dy, a, b) and not aligned(dx, dy, a, b)
  v_sel[(dx, dy)] = list(filter(f, vects))

cache = {}
def f(p, x, y, dx, dy):
  key = p, x, y, dx, dy
  if p * p < x * x +  y * y: return 0
  if x == 0 and (dx != 0 or dy != -1): return int(0 <= y)
  if (x != 0 or y != 0) and not lower(dx, dy, -x, -y): return 0
  if key in cache: return cache[key]
  res = sum([f(p-c, x+a, y+b, a, b) if 0 <= x+a else 0 for a, b, c in v_sel[(dx, dy)]])
  cache[key] = res
  return res

print f(max_p, 0, 0, 0, -1) # Start by heading down
