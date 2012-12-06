import itertools

def nb_combs(blocks, c_set, u_set, sum_w, min_x, max_x):
  if blocks == 0:
    if sum_w == 0:
      is_sym = True
      for (x, y) in c_set:
        if not (-x, y) in c_set:
          is_sym = False
          break
      return 1 + int(is_sym)
    else: return 0
  res = 0
  bb = (blocks * (blocks + 1)) / 2
  max_w = sum_w + max_x * blocks + bb
  min_w = sum_w + min_x * blocks - bb
  if min_w > 0 or max_w < 0: return 0
  u_set = set(u_set)
  tmp_set = set(c_set)
  for (x, y) in c_set:
    for (dx, dy) in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
      new_x, new_y = x + dx, y + dy
      if new_y <= 0 or (new_x, new_y) in u_set: continue
      tmp_set.add((new_x, new_y))
      u_set.add((new_x, new_y))
      res += nb_combs(blocks-1, tmp_set, u_set, sum_w+new_x, min(min_x, new_x), max(max_x, new_x))
      tmp_set.remove((new_x, new_y))
  return res

print nb_combs(18, set([(0, 0)]), set([(0, 0)]), 0, 0, 0) / 2
