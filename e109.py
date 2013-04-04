cells = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 25]

cache = {}

def c(score, darts, prev):
  key = (score, darts, prev)
  if cache.has_key(key):
    return cache[key]
  res = 0
  for i in cells:
    if 2 * i == score:
      res += 1
    for m in [1, 2, 3]:
      if i == 25 and m == 3:
        continue
      v = m * i
      if 100 * m + i >= prev and score > v and darts > 1:
        res += c(score - v, darts - 1, 100 * m + i)
  cache[key] = res
  return res

print sum([c(i, 3, 1) for i in range(1, 100)])
