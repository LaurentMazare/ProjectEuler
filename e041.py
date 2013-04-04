import sys
import random
from itertools import permutations

def binary_digits(n):
  res = []
  while n > 0:
    res.append(n % 2)
    n = n / 2
  return res

def MillerRabin(n, s = 50):
  b = binary_digits(n - 1)
  for _ in xrange(s):
    a = random.randint(1, n - 1)
    a = 6738399
    d = 1
    for i in xrange(len(b) - 1, -1, -1):
      x, d = d, (d * d) % n
      if d == 1 and x != 1 and x != n - 1: return False
      if b[i] == 1: d = (d * a) % n
    if d != 1: return False
  return True

current_max = 0
for p in permutations('7654321'):
  x = 0
  for n in p:
    x = 10*x+int(n)
  if x > current_max and MillerRabin(x): current_max = x
print current_max
