import itertools
n = 36

#First generate all the line equations for the triangle
#Equations have the form (a, b, c) for ax + by = c
all_segs = set((1.0, 0.0, float(n)/2.0) for n in xrange(1, 2*n))
all_segs |= set((0.0, 1.0, float(n)) for n in xrange(0, n))
all_segs |= set((1.0, 1.5, float(n)) for n in xrange(1, 2*n))
all_segs |= set((2.0, 1.0, (float(n)+1.0)*2.0) for n in xrange(0, n))
all_segs |= set((1.0, -1.5, float(n)) for n in xrange(1-n, n))
all_segs |= set((2.0, -1.0, float(n)*2.0) for n in xrange(0, n))
print len(all_segs)

def too_close(p1, p2):
  return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2 < 1e-10

#Finds the intersection between two lines
#Return None if not in the main triangle
def intersect((a1, b1, c1), (a2, b2, c2)):
  if (a1, b1) == (a2, b2):
    return None
  y = (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1)
  x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1)
  if y < -1e-5 or y - 2.0*x > 1e-5 or 2.0*x + y > 2.0*n + 1e-5:
    return None
  return (x, y)

nb = 0
nb_total = 0
#For all triple of equations, look at the intersections
for (eq1, eq2, eq3) in itertools.combinations(all_segs, 3):
  nb_total += 1
  x12 = intersect(eq1, eq2)
  x13 = intersect(eq1, eq3)
  x23 = intersect(eq2, eq3)
  if x12 == None or x13 == None or x23 == None:
    continue
  if too_close(x12, x23) or too_close(x12, x13) or too_close(x13, x23):
    continue
  #If intersections are disctinct and in the main triangle, add 1 to nb
  nb += 1

print (nb, nb_total)
