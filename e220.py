def size(s, n):
  res = 0
  for x in s:
    if x == 'F':
      res += 1
    elif x == 'a' or x == 'b':
      res += 2 ** n - 1
  return res

cache = {}
def h(s, steps, n, dx, dy):
  key = (s, steps, n, dx, dy)
  if cache.has_key(key):
    return cache[key]
  x = 0
  y = 0
  for c in s:
    if c == 'F':
      if steps == 0:
        break
      steps -= 1
      x += dx
      y += dy
    elif c == 'R':
      (dx, dy) = (dy, -dx)
    elif c == 'L':
      (dx, dy) = (-dy, dx)
    elif (c == 'a' or c == 'b') and n != 0:
      s_subst = size(c, n)
      if c == 'b':
        subst = "LFaLb"
      elif c == 'a':
        subst ="aRbFR"
      (tmp_x, tmp_y, dx, dy) = h(subst, min(steps, s_subst), n-1, dx, dy)
      x += tmp_x
      y += tmp_y
      steps -= min(steps, s_subst)
  res = (x, y, dx, dy)
  cache[key] = res
  return res

res = h("Fa", 10**12, 50, 0, 1)
print "%d,%d" % (res[0], res[1])
