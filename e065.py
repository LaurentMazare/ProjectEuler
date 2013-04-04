def frac(n):
  l = range(n)
  for i in range(n):
    if (i % 3 == 1): l[i]=2*(1+i/3)
    else: l[i] = 1
  num = 0
  den = 0
  for i in l[::-1]:
    if den == 0:
      num = 1
      den = i
    else:
      tmp = den
      den = den * i + num
      num = tmp
  result = num + 2*den
  result = str(result)
  s = 0
  for x in result:
    s += int(x)
  print(s)

frac(99)
