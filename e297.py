target = pow(10, 17)
fib = [ 1 ]
zeck = [ 0, 1, 2, 3 ]
x_n = 1
x_np = 1
i = 0
while x_n <= target:
  x_n, x_np = x_np, x_n + x_np
  fib.append(x_n)
  if i >= 4: zeck.append(zeck[i-1]+zeck[i-2]+fib[i-2]-1)
  i += 1

def res(n):
  if n == 0: return 0
  if n == 1: return 1
  for i in range(0, len(fib)):
    if fib[i]>n: break
  i -= 1
  return zeck[i]+res(n-fib[i])+n-fib[i]

print res(target-1)
