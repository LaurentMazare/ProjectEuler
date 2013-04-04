
def f(n):
  p = n
  q = 1
  for i in range(0, 16):
    p, q = p*p + n*q*q, 2*p*q
  digits = (pow(10, 105) * p)/q
  res = 0
  s = str(digits)
  for i in range(0, 100):
    res += int(s[i])
  return res

squares = []
for i in range(1, 10):
  squares.append(i*i)

res = 0
for i in range(2, 100):
  if not i in squares:
    res += f(i)
print(res)
