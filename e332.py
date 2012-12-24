import itertools
from math import *

def sqr(x): return x * x
def dot((x1, y1, z1), (x2, y2, z2)): return x1*x2+y1*y2+z1*z2
def norm((x, y, z)): return sqrt(sqr(x)+sqr(y)+sqr(z))
def determ((x1, y1, z1), (x2, y2, z2), (x3, y3, z3)):
  res = x1 * (y2 * z3 - y3 * z2)
  res -= y1 * (x2 * z3 - x3 * z2)
  return res + z1 * (x2 * y3 - x3 * y2)

# Applying L'Huiller's theorem doesn't seem to have the necessary precision
# So instead we use Oosterom and Strackee as described on Wikipedia
def area(p1, p2, p3):
  det = determ(p1, p2, p3)
  norm1 = norm(p1)
  norm2 = norm(p2)
  norm3 = norm(p3)
  d12 = dot(p1, p2)
  d13 = dot(p1, p3)
  d23 = dot(p2, p3)
  div = norm1*norm2*norm3 + d12*norm3 + d13*norm2 + d23*norm1
  a = atan2(det, div)
  return 2.0 * (a + (pi if a < 0.0 else 0.0))

total_a = 0.0
for r in xrange(1, 51):
  r_f = float(r)
  min_a = 1e10
  points = []
  for x in xrange(0, r+1):
    for y in xrange(0, r+1):
      z2 = r * r - x * x - y * y
      if z2 < 0.0: continue
      z = int(0.5 + sqrt(z2))
      if z * z == z2:
        points.append((x/r_f,  y/r_f,  z/r_f))
        points.append((x/r_f,  y/r_f, -z/r_f))
        points.append((x/r_f, -y/r_f,  z/r_f))
        points.append((x/r_f, -y/r_f, -z/r_f))
  for p1, p2, p3 in itertools.combinations(points, 3):
    a = area(p1, p2, p3)
    if a <= 1e-12: continue
    min_a = min(a * r_f * r_f, min_a)
  total_a += min_a
  print r, len(points), min_a
print "%.6f" % total_a
