cache = {}
def f(n, has_l, previous_a):
  if n == 0:
    return 1
  key = str(n) + " " + str(has_l) + " " + str(previous_a)
  if cache.has_key(key):
    return cache[key]
  res = f(n-1, has_l, 0)
  if not has_l:
    res += f(n-1, True, 0)
  if previous_a < 2:
    res += f(n-1, has_l, previous_a+1)
  cache[key]=res
  return res

print( f(30, False, 0) )
    
  
