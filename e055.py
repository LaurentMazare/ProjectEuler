def rev(n):
  res = 0
  while (n!=0):
    res = 10 * res + n % 10
    n /= 10
  return res

def is_pal(n):
  n = str(n)
  l = len(n)
  for i in range(l/2):
    if (n[i]!=n[l-i-1]): return 0
  return 1

def is_lychrel(x):
  for i in range(50):
    x += rev(x)
    if is_pal(x): return 0
  return 1

i=0
for n in range(10000):
  if (is_lychrel(n)):
    i += 1
print(i)
