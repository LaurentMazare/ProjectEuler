import sys
def gcd(a, b):
  if b == 0: return a
  else: return gcd(b, a % b)

def simp(a, b):
  g = gcd(a, b)
  return a/g, b/g

nbs = [(5248, 640), (1312, 1888), (2624, 3776), (5760, 3776), (3936, 5664)]

def init(i):
  nA, nB = nbs[i]
  pqs = set()
  for mA in xrange(1, nA):
    for mB in xrange(1, nB):
      p, q = simp(nA*mB, mA*nB)
      if p > q: pqs.add((p, q))
  return pqs

# First create all potential m = p/q using equation 1.
pqs = init(1)
print "Start: ", len(pqs)
# Then filter out the potential (p, q) using all equations
for nA, nB in nbs:
  to_delete = []
  for p, q in pqs:
    left, right = simp(p*nB, q*nA)
    if left > nB or right > nA: to_delete.append((p, q))
  for td in to_delete: pqs.remove(td)
print "Filtered: ", len(pqs)
pqs = list(pqs)
pqs.sort(lambda (p, q), (pp, qq): pp*q-p*qq)
# And test all possible p, q
for p, q in pqs:
  nA0, nB0 = nbs[0]
  left0, right0 = simp(p*nB0, q*nA0)
  k0 = 0
  nA3, nB3 = nbs[3]
  left3, right3 = simp(p*nB3, q*nA3)
  # Equations 1, 2, and 4 have the same form 59p.mA = 41q.mB
  # So we can solve for the sum mAS, mBS of their mA/mB simultaneously
  nAS, nBS = nbs[1][0] + nbs[2][0] + nbs[4][0], nbs[1][1] + nbs[2][1] + nbs[4][1]
  leftS, rightS = simp(59*p, 41*q)
  while True:
    k0 += 1
    mA0, mB0 = right0 * k0, left0 * k0
    if mA0 > nA0 or mB0 > nB0: break
    k3 = 0
    while True:
      k3 += 1
      mA3, mB3 = right3 * k3, left3 * k3
      if mA3 > nA3 or mB3 > nB3: break
      kS = 0
      while True:
        kS += 1
        mAS, mBS = rightS * kS, leftS * kS
        if mAS > nAS or mBS > nBS: break
        sumMA, sumMB = mA0 + mA3 + mAS, mB0 + mB3 + mBS
        sumNA, sumNB = nA0 + nA3 + nAS, nB0 + nB3 + nBS
        if q * sumNB * sumMA == p * sumMB * sumNA:
          print "%d/%d" % (p, q)
          sys.exit()
