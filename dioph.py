from math import sqrt
from itertools import takewhile

def gcd(x, y): return x if y == 0 else gcd(y, x % y)

def extended_gcd(a, b):
  if b == 0: return (1, 0)
  q, r = div_mod(a, b)
  s, t = extended_gcd(b, r)
  return t, s - q*t

# PQa algorithm as described in: http://www.jpr2718.org/pell.pdf
# This performs the continued fraction expansion for (p0+sqrt(d))/q0
def pqa(p0, q0, d):
  sqrt_d = sqrt(d)
  assert 0 < d, "D cannot be negative or zero"
  assert q0 != 0, "Q0 cannot be zero"
  assert (p0*p0 - d) % q0 == 0, "P0^2 cannot be different from D modulo Q0"
  assert int(sqrt_d) * int(sqrt_d) != d, "D cannot be a perfect square"
  a_i, a_im = 1, 0
  b_i, b_im = 0, 1
  g_i, g_im = q0, -p0
  p_i, q_i = p0, q0
  i, ir = -1, None
  alphas = []
  while True:
    i += 1
    xi_i = (p_i + sqrt_d)/q_i
    xibar_i = (p_i - sqrt_d)/q_i
    alpha_i = int(xi_i)
    a_i, a_im = alpha_i * a_i + a_im, a_i
    b_i, b_im = alpha_i * b_i + b_im, b_i
    g_i, g_im = alpha_i * g_i + g_im, g_i
    # Everything is now as of i
    if ir == None and 1 < xi_i and -1 < xibar_i and xibar_i < 0:
      ir, p_ir, q_ir = i, p_i, q_i
    if ir != None and ir != i and p_i == p_ir and q_i == q_ir: break
    alphas.append(alpha_i)
    # Update p_i and q_i for i+1
    p_i = alpha_i * q_i - p_i
    q_i = (d - p_i * p_i) / q_i
  return alphas, i - ir

# Get the minimal solution for x^2 - d.y^2 = epsilon, where epsilon can be 1 or -1
def pell1_min(d, epsilon):
  assert epsilon == 1 or epsilon == -1, "epsilon is different from -1 and 1"
  alphas, l = pqa(0, 1, d)
  if l & 1: # l is even
    index = 2*l - 1 if epsilon == 1 else l-1
  else: # l is odd
    if epsilon == -1: return None
    index = l-1
  b_i, b_im = 0, 1
  g_i, g_im = 1, 0
  pre_l = len(alphas) - l
  for i in xrange(0, 1+index):
    alpha_i = alphas[i] if i < pre_l else alphas[pre_l + (i - pre_l) % l]
    b_i, b_im = alpha_i * b_i + b_im, b_i
    g_i, g_im = alpha_i * g_i + g_im, g_i
  return g_i, b_i

# Yield all the solutions solution for x^2 - d.y^2 = epsilon, where epsilon can be 1 or -1
def pell1(d, epsilon):
  min_sol = pell1_min(d, epsilon)
  if min_sol == None: return
  t, u = min_sol
  x, y = t, u
  n = 0
  while True:
    if epsilon == 1 or n % 2 == 0: yield x, y
    x, y, n = t*x + u*y*d, t*y + u*x, n+1

if __name__ == "__main__":
  print "Testing GCD..."
  assert gcd(3, 1) == 1, "GCD failed"
  assert gcd(3, 9) == 3, "GCD failed"
  assert gcd(48, 18) == 6, "GCD failed"
  print "Testing PQa..."
  assert pqa(11, 108, 13) == ([0, 7, 2, 1, 1, 6, 1, 1], 5), "PQa failed"
  assert pqa(0, 1, 13) == ([3, 1, 1, 1, 1, 6], 5), "PQa failed"
  print "Testing pell1_min..."
  assert pell1_min(13, 1) == (649, 180), "pell1_min failed"
  assert pell1_min(13, -1) == (18, 5), "pell1_min failed"
  print "Testing pell1..."
  assert list(takewhile(lambda (x, _): x < 1000000, pell1(13, 1))) == [(649, 180), (842401, 233640)], "pell1 failed"
  assert list(takewhile(lambda (x, _): x < 1000000, pell1(13, -1))) == [(18, 5), (23382, 6485)], "pell1 failed"


