n = 30

cache2 = {}
def c2(x, y):
  if x == 1 or y == 1: return 1
  if (x, y) in cache2: return cache2[(x, y)]
  res = c2(x-1, y) + c2(x, y-1)
  cache2[(x, y)] = res
  return res

cache3 = {}
def c3(x, y):
  if x == 0: return c2(n, y)
  if y == 0: return c2(n, x)
  if (x, y) in cache3: return cache3[(x, y)]
  res = 0
  for z in xrange(1, 1+y):
    res += c3(z, x-1)
  if x == 1:
    res += c5(n-1, y)
  else:
    for z in xrange(1, n+1):
      res += c2(z, x-1) * c5(y, n-z)
  cache3[(x, y)] = res
  return res

cache1 = {}
def c1(x, y):
  if x == 0: return c3(n, y)
  if y == 0: return c3(n, x)
  if (x, y) in cache1: return cache1[(x, y)]
  res = 0
  for yy in xrange(0, y+1):
    res += c1(x-1, yy)
  for z in xrange(1, n):
    res += c5(y, z) * c3(x-1, n-z)
  if x == 1:
    res += c4(n-1, y)
  else:
    for z in xrange(0, n):
      res += c4(z, y) * c2(n-z, x-1)
  cache1[(x, y)] = res
  return res

cache5 = {}
def c5(x, y):
  if x == 0 or y == 0: return 1
  if (x, y) in cache5: return cache5[(x, y)]
  res = c5(x-1, y)
  if x == 1: res += c6(y-1)
  else:
    for z in xrange(1, 1+y):
      res += c6(y-z) * c2(x-1, z)
  cache5[(x, y)] = res
  return res

def c6(x): return x+1

cache4 = {}
def c4(x, y):
  if x == 0: return c5(n, y)
  if y == 0: return c5(n, x)
  if (x, y) in cache4: return cache4[(x, y)]
  res = c4(x-1, y)
  for z in xrange(1, y+1):
    res += c6(y-z) * c3(x-1, z)
  if x == 1:
    res += c7(n-1, y)
  else:
    for z in xrange(1, n+1):
      res += c7(y, n-z) * c2(x-1, z)
  cache4[(x, y)] = res
  return res

cache7 = {}
def c7(x, y):
  if x == 0: return c6(y)
  if y == 0: return c6(x)
  if (x, y) in cache7: return cache7[(x, y)]
  res = c7(x-1, y) + c5(x-1, y)
  if x == 1: res += c8(y-1)
  else:
    for z in xrange(1, y+1):
      res += c2(x-1, z) * c8(y-z)
  cache7[(x, y)] = res
  return res

cache8 = {}
def c8(y):
  if y == 0: return 2
  if y in cache8: return cache8[y]
  res = c8(y-1) + c6(y) + 1
  cache8[y] = res
  return res

def c():
  res = c1(n-1, n-1)
  for x in xrange(1, n):
    res += c2(n-1, x) * c3(n, n-x)
  for x in xrange(1, n+1):
    res += c3(n-1, n-x) * c2(n, x)
  return res

print c()
