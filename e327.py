def m(c, r):
  if r == 0:
    return 1
  prev_m = m(c, r-1)
  if prev_m < c:
    return 1 + prev_m
  res = prev_m + 2 * ((prev_m - c + 1 + c - 3) / (c-2)) + 1
  return res

res = 0
for c in range(3, 41):
  res += m(c, 30)
print res
