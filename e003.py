n = 600851475143
d = 2
while True:
  while n % d == 0: n /= d
  if n == 1: break
  d = d + 1
print d
