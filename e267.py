from math import log, ceil

M = 1000000000
n = 1000
def obj(f):
  res = (log(1+2*f)-log(1-f))*n/(1-f) - (log(M) - n*log(1-f))*(2/(1+2*f)+1/(1-f))
  return res

def bound(f):
  res = (log(M)-n*log(1-f))/(log(1+2*f)-log(1-f))
  return res

low = 1e-6
up = 1 - 1e-6
eps = 1e-16

while up - low > eps:
  mid = (low + up) / 2
  if obj(mid) > 0:
    up = mid
  else:
    low = mid

def fact(n):
  res = 1
  for i in range(2, n+1):
    res *= i
  return res

prob = 0
base = pow(2, n)
lower = int(ceil(bound(mid)))
for p in range(lower, n+1):
  prob += fact(n)/(fact(p)*fact(n-p))
prob *= pow(10, 15)
print(prob/base/1e15)
