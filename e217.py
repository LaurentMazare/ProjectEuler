cache = {}

def aux(sizem, sizep, middle, diff):
  if sizem == 0 and middle == 0 and sizep == 0:
    return 0, 1 if diff == 0 else 0
  key = (sizem, sizep, middle, diff)
  if not key in cache:
    s, nb = 0, 0
    for x in xrange(0, 10):
      if sizep > 0:
        current_s, current_nb = aux(sizem, sizep-1, middle, diff + x)
      elif middle == 1:
        current_s, current_nb = aux(sizem, sizep, 0, diff)
      else:
        if sizem == 1 and x == 0: continue
        current_s, current_nb = aux(sizem - 1, sizep, 0, diff - x)
      nb += current_nb
      s += current_s * 10 + current_nb * x
    cache[key] = s, nb
  return cache[key]

def balanced(max_n):
  s = 0
  for n in xrange(1, max_n + 1):
    current_s, _ = aux(n/2, n/2, n%2, 0)
    s += current_s
  return s

print balanced(5)
print balanced(47) % (3**15)
