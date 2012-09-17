start = (0, sum([1 << x for x in [1, 4, 5, 8, 9, 12, 13]]))
stop = (0, sum([1 << x for x in [2, 5, 7, 8, 10, 13, 15]]))
def get_next((white, reds)):
  all_nexts = []
  is_red = lambda x: (reds & (1 << x)) > 0
  new_whites = []
  if white > 3: new_whites.append((68, white - 4))
  if white < 12: new_whites.append((85, white + 4))
  if white % 4 != 0: new_whites.append((82, white - 1))
  if white % 4 != 3: new_whites.append((76, white + 1))
  for dir, new_white in new_whites:
    if is_red(white) and not is_red(new_white):
      new_reds = reds - (1 << white)
    elif is_red(new_white) and not is_red(white):
      new_reds = reds + (1 << white)
    else:
      new_reds = reds
    all_nexts.append((dir, (new_white, new_reds)))
  return all_nexts

reachable = set([start])    # All the reachable states for the BFS
current = {start: set([0])} # The different codes used to reach each state

while stop not in current:
  print len(reachable)
  tmp = {}
  to_add = set()
  for config, codes in current.iteritems():
    for direction, next in get_next(config):
      if not next in reachable:
        to_add.add(next)
        if not next in tmp: tmp[next] = set()
        for code in codes:
          tmp[next].add((code * 243 + direction) % 100000007)
  reachable |= to_add
  current = tmp
print sum(current[stop])
