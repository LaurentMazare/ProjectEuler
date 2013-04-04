def nb_digits(n):
  d = 0
  while n!=0:
    d+=1
    n/=10
  return d

p = 1
q = 1
nb = 0
for i in range(1, 1001):
  p, q = p+2*q, p+q
  if nb_digits(p) > nb_digits(q): nb+=1
print(nb)
