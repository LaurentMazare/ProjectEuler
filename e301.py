cache = {}

def nb_seq(l, start):
  if l == 0: return 0
  if l == 1: return 1
  if cache.has_key((l, start)):
    return cache[l, start];
  if start == 0:
    res = nb_seq(l-1, 0) + nb_seq(l-1, 1)
  elif start == 1:
    res = nb_seq(l-1, 0)
  cache[l, start] = res
  return res

print nb_seq(30,0)+nb_seq(30,1)
