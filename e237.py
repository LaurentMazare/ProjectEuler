# 0 to 8 are the possible ways to cross a vertical line

allowed_transitions = set([
  (0,0), (0,2), (2,1), (0,8), (0,7), (7,1),
  (1,1), (1,4), (4,0),
  (2,4), (3,6), (4,5), (4,7), (4,8),
  (4,2), (6,3), (5,4), (7,4), (8,4)
])

mod = 10 ** 8
cache = {}
def t(inp, out, width):
  key = (inp, out, width)
  if cache.has_key(key):
    return cache[key]
  if width == 1:
    if (inp, out) in allowed_transitions:
      return 1
    else:
      return 0
  res = 0
  left_width = width / 2
  right_width = width - left_width
  for i in range(0, 8):
    comb = t(inp, i, left_width) * t(i, out, right_width)
    res += comb
  res = res % mod
  cache[key] = res
  return res

print t(4, 8, 10 ** 12)
