a, b, c = 21 ** 7, 7 ** 21, 12 ** 7

n = b
res = 0
ff = b + 4 * (a-c)
while n >= 0:
  aa = a if n >= a - 1 else n + 1
  res += ff * aa - ((aa-1)*aa)/2
  ff += 3 * (a-c)
  n -= aa
print res
