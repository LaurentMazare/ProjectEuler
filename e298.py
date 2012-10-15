cache = {}

def e(mem_l, mem_r, nb_rounds, l_minus_r):
  if nb_rounds == 0: return abs(l_minus_r)
  # Normalize mem_l and mem_r
  renaming = {None: None}
  tmp_name = 1
  for i in xrange(0, 5):
    for elem in [mem_l[i], mem_r[i]]:
      if not elem in renaming:
        renaming[elem] = tmp_name
        tmp_name += 1
  mem_l = renaming[mem_l[0]], renaming[mem_l[1]], renaming[mem_l[2]], renaming[mem_l[3]], renaming[mem_l[4]]
  mem_r = renaming[mem_r[0]], renaming[mem_r[1]], renaming[mem_r[2]], renaming[mem_r[3]], renaming[mem_r[4]]
  key = (mem_l, mem_r, nb_rounds, l_minus_r)
  if key in cache: return cache[key]
  res = 0.0
  for x in xrange(1, 11):
    tmp_lmr = int(x in mem_l) - int(x in mem_r)
    tmp_l = mem_l if x in mem_l else (mem_l[1], mem_l[2], mem_l[3], mem_l[4], x)
    if x == mem_r[1]: tmp_r = mem_r[0], mem_r[2], mem_r[3], mem_r[4], x
    elif x == mem_r[2]: tmp_r = mem_r[0], mem_r[1], mem_r[3], mem_r[4], x
    elif x == mem_r[3]: tmp_r = mem_r[0], mem_r[1], mem_r[2], mem_r[4], x
    elif x == mem_r[4]: tmp_r = mem_r
    else: tmp_r = mem_r[1], mem_r[2], mem_r[3], mem_r[4], x
    res += 0.1 * e(tmp_l, tmp_r, nb_rounds-1, l_minus_r+tmp_lmr)

  cache[key] = res
  return res

init_mem = None, None, None, None, None
print "%.8f" % e(init_mem, init_mem, 50, 0)
