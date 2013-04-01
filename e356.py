# The largest root r1 of x^3-2^n*x^2+n = 0 is close to 2^n
# whereas the two other roots r2 and r3 are close to 0 (abs(r2)<1, abs(r3)<1)
#
# Consider the recurence relation u_{k+3} = 2^n.u_{k+2} - n.u_k
# Closed form solutions have the form u_k = x.r1^k + y.r2^k + z.r3^k
# With x = y = z = 1, this will converge to r1^k+r2^k+r3^k (r2^k+r3^k is very small)
# So we use modular exponentiation starting with:
# u_0 = 3 (=x+y+z)
# u_1 = 2^n (=r1+r2+r3)
# u_2 = 2^(2*n) (=r1^2+r2^2+r3^2)
mod = 10**8

def multm(A, B):
  n = len(A)
  C = [[0] * n for _ in xrange(n)]
  for i in xrange(n):
    for j in xrange(n):
      C[i][j] = sum(A[i][k]*B[k][j] for k in xrange(n)) % mod
  return C

def powmod(A, n):
  if n == 1: return A
  elif n & 1: return multm(A, powmod(A, n-1))
  return powmod(multm(A, A), n/2)

def multv(A, v):
  n = len(v)
  return [sum([A[i][k]*vk for k, vk in enumerate(v)]) for i in xrange(n)]

res = 0
for n in xrange(1, 31):
  M = [[0, 1, 0], [0, 0, 1], [-n, 0, 2**n]]
  M = powmod(M, 987654321)
  res += multv(M, [3, 2**n, 2**(2*n)])[0] - 1
print res % mod

