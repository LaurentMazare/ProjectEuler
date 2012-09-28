cache = {}
# Dynamic programming on edges, edges are coded in
# base 3, 0: nothing, 1: ant in, 2: ant out
def f(size_x, size_y, left, right, up, down):
  if size_x == 1 and size_y == 1:
    # only returns one if one ant in and one ant out
    return 1 if left + right + up + down == 3 and max(left, right, up, down) == 2 else 0
  if size_x > size_y: return f(size_y, size_x, up, down, left, right)
  key = (size_x, size_y, left, right, up, down)
  if key in cache: return cache[key]
  res = 0
  for border in xrange(0, 3 ** size_y):
    size_y1, size_y2 = size_y / 2, size_y - size_y / 2
    s = 3 ** size_y1
    left1, left2 = left % s, left / s
    right1, right2 = right % s, right / s
    f1 = f(size_x, size_y1, left1, right1, border, down)
    f2 = f(size_x, size_y2, left2, right2, up, border)
    res += f1 * f2
  cache[key] = res
  return res

print f(4, 4, 0, 0, 0, 0)
print f(10, 10, 0, 0, 0, 0)
