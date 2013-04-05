sA = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
sB = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"

def size(n):
  lA = len(sA)
  lB = len(sB)
  if n == 1:
    return lA
  if n == 2:
    return lB
  prev = lA
  res = lB
  for i in range(3, 1+n):
    (prev, res) = (res, prev + res)
  return res

def aux(i, n):
  if n == 1:
    return sA[i-1]
  if n == 2:
    return sB[i-1]
  s = size(n-2)
  if i > s:
    return aux(i-s, n-1)
  else:
    return aux(i, n-2)

def d(i):
  for n in range(1, 10000):
    if size(n) > i:
      return aux(i, n)

print sum([10 ** n * int(d((127 + 19*n) * 7 ** n)) for n in xrange(0, 18)])
