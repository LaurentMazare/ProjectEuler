from math import *
def is_prime(n):
  m = 1 + int(sqrt(n))
  for i in range(2, m):
    if n % i == 0:
      return False
  return True

def next_prime(n):
  while not is_prime(n):
    n += 1
  return n

primes = []
next_p = 2
for i in range(0, 10):
  primes.append(next_p)
  next_p = next_prime(next_p+1)

bound = pow(10,9)
pseudo = []
def f(level, v):
  while True:
    v *= primes[level]
    if v > bound:
      break
    next_p = next_prime(v+2)
    dist = next_p - v
    if not dist in pseudo:
      pseudo.append(dist)
    f(level+1, v)

f(0, 1)
print sum(pseudo)
