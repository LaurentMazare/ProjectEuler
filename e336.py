import itertools
cache = {}

def m(l):
  key = str(l)
  index = -1
  for i, elem in enumerate(l):
    if i != elem:
      index = i
      break
  if index == -1:
    return 0
  if index == len(l) - 2:
    return 1
  if cache.has_key(key):
    return cache[key]
  for index_bis, elem_bis in enumerate(l):
    if elem_bis == index:
      break
  res = 0
  if index_bis != len(l) - 1:
    for i in range(index_bis, (index_bis + len(l)) / 2):
      l[i], l[index_bis-i-1] = l[index_bis-i-1], l[i]
    res += 1
  for i in range(index, (index + len(l)) / 2):
    l[i], l[index-i-1] = l[index-i-1], l[i]
  res += 1
  res += m(l)
  cache[key] = res
  return res

def to_str(l):
  res = ""
  for i in l:
    res += chr(ord('A')+i)
  return res

max_mm = 0
wagons = 11
perms = itertools.permutations(range(0, wagons))
x = 0
for perm in perms:
  mm = m(list(perm))
  max_mm = max(mm, max_mm)
  if mm == 2 * wagons - 3:
    x += 1
    print (x, to_str(perm), max_mm)
    if x == 2011:
      break
