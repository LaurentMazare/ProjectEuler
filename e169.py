cache = {}

def f(x):
  if x == 1:
    return 1
  if x == 0:
    return 1
  if cache.has_key(x):
    return cache[x]
  if x % 2 == 1:
    res = f((x-1)/2)
  else:
    res = f(x/2) + f(x/2 - 1)
  cache[x] = res
  return res

print f(pow(10,25))
