f, prev, total = 1, 1, 0
while f < 4*10**6:
  if not f & 1: total += f
  f, prev = f + prev, f
print total
