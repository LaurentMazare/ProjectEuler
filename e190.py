import numpy
res = 0
for m in range(2, 16):
  a = numpy.zeros((m-1, m-1), float)
  b = numpy.zeros(m-1, float)
  for k in range(0, m-1):
    r = float(k+2) / float(k+3)
    for j in range(0, m-1):
      a[k, j] = r
    a[k, k] = 1
    b[k]= r * m
  x = numpy.linalg.solve(a, b)
  product = float(m) - float(sum(x))
  for k in range(0, m-1):
    product *= pow(x[k], k+2)
  res += int(product)
print res
