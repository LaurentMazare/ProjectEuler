from math import sqrt
import itertools
current_s = 290797
def bbs():
  global current_s
  current_s = (current_s * current_s) % 50515093
  return (current_s % 2000) - 1000

def same_side((x1, y1), (x2, y2), (x3, y3), (x, y)):
  vx = x2 - x1
  vy = y2 - y1
  d1 = - vy * (x3 - x1) + vx * (y3 - y1)
  d2 = - vy * (x - x1) + vx * (y - y1)
  return (d1 >= 0 and d2 >= 0) or (d1 <= 0 and d2 <= 0)

def is_in(p1, p2, p3, p):
  return same_side(p1, p2, p3, p) and same_side(p1, p3, p2, p) and same_side(p2, p3, p1, p)

def add_tri(tris, p1, p2, v):
  key = min(p1, p2), max(p1, p2)
  if not key in tris: tris[key] = []
  tris[key].append(v)
  
def iter_rec(p1, p2, p3, p4, points, tris, prev_area):
  max_a = prev_area
  for p5, area in tris.get((min(p1, p4), max(p1, p4)), []):
    if (not p5 in points) and same_side(p3, p4, p5, p1) and same_side(p4, p5, p1, p2) and same_side(p1, p5, p2, p4):
      points.add(p5)
      max_a = max(max_a, iter_rec(p1, p2, p4, p5, points, tris, area + prev_area))
      points.remove(p5)
  return max_a

def d((x1, y1), (x2, y2)): return sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def max_area(nb_points):
  points = [(bbs(), bbs()) for i in xrange(0, nb_points)]
  tris = {}
  for p1, p2, p3 in itertools.combinations(points, 3):
    empty = True
    for p in points:
      if p != p1 and p != p2 and p != p3 and is_in(p1, p2, p3, p):
        empty = False
        break
    if empty:
      a, b, c = d(p1, p3), d(p1, p2), d(p2, p3)
      s = (a + b + c) / 2
      area = sqrt(s * (s-a) * (s-b) * (s-c))
      add_tri(tris, p1, p2, (p3, area))
      add_tri(tris, p1, p3, (p2, area))
      add_tri(tris, p3, p2, (p1, area))
  max_a = 0.0
  for (p1, p2), rest in tris.iteritems():
    for p3, area in rest:
      area = iter_rec(p1, p2, p2, p3, set([p1, p2, p3]), tris, area)
      max_a = max(area, max_a)
  return max_a

print "%.1f" % max_area(500)
