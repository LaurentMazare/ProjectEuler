import numpy

def f(n):
  return 1 - n + n ** 2 - n ** 3 + n ** 4 - n ** 5 + n ** 6 - n ** 7 + n ** 8 - n ** 9 + n ** 10

s_fit = 0
for i in range(1, 11):
  a = numpy.zeros((i, i), float)
  b = numpy.zeros(i, float)
  for j in range(0, i):
    for k in range(0, i):
      a[j][k] = (1+j) ** k
    b[j] = f(1+j)
  poly = numpy.linalg.solve(a, b)
  for j in range(1, 15):
    op = 0
    for m in range(0, i):
      pp = int(poly[m]-0.5)
      if poly[m] > 0:
        pp += 1
      op += pp * j ** m
    if abs(op - f(j)) > 1e-7:
      s_fit += op
      break
print s_fit
