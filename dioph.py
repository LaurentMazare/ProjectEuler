from math import sqrt
from itertools import takewhile

def gcd(x, y): return x if y == 0 else gcd(y, x % y)

def extended_gcd(a, b):
  if b == 0: return (1, 0)
  q, r = divmod(a, b)
  s, t = extended_gcd(b, r)
  return t, s - q*t

# Returns s such that s*s = x if x is a perfect square.
# Otherwise returns -1. This implementation is based on using sqrt,
# so only valid for 'small' integers.
def sqrt_int(x):
  s = int(sqrt(x))
  return s if s*s == x else -1

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

# Get the minimal solution for x^2 - d.y^2 = 4*epsilon, where epsilon can be 1 or -1
def pell4_min(d, epsilon):
  assert epsilon == 1 or epsilon == -1, "epsilon is different from -1 and 1"
  d_mod_4 = d % 4
  if d_mod_4 == 0:
    res1 = pell1_min(D/4, epsilon)
    if res1 == None: return None
    return 2*res1[0], res1[1]
  if d_mod_4 == 2 or d_mod_4 == 3:
    res1 = pell1_min(D, epsilon)
    if res1 == None: return None
    return 2*res1[0], 2*res1[1]
  assert d_mod_4 == 1, "d_mod_4 is different from one"
  alphas, l = pqa(1, 2, d)
  if l % 2 == 0 and epsilon == -1: return None
  b_i, b_im = 0, 1
  g_i, g_im = 2, -1
  pre_l = len(alphas) - l
  for i in xrange(0, l):
    alpha_i = alphas[i] if i < pre_l else alphas[pre_l + (i - pre_l) % l]
    b_i, b_im = alpha_i * b_i + b_im, b_i
    g_i, g_im = alpha_i * g_i + g_im, g_i
  # If l is odd, solution to the -4 equation.
  # If l is even, solution to the +4 equation.
  # So the only case where we have to change g and b is when l is odd and epsilon is 1
  if l % 2 == 1 and epsilon == 1:
    return (g_i*g_i + b_i*b_i*d)/2, g_i*b_i
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

# Yield all the solutions solution for x^2 - d.y^2 = 4*epsilon, where epsilon can be 1 or -1
def pell4(d, epsilon):
  min_sol = pell4_min(d, epsilon)
  if min_sol == None: return
  t, u = min_sol
  x, y = t, u
  n = 0
  while True:
    if epsilon == 1 or n % 2 == 0: yield x, y
    x, y, n = (t*x + u*y*d)/2, (t*y + u*x)/2, n+1

def pell_funds_bf(d, n):
  t, u = pell1_min(d, 1)
  if 0 < n: l1, l2 = 0, int(sqrt((n*(t-1))/(2.0*d)))
  else: l1, l2 = int(sqrt(-n/(1.0*d))), int(sqrt((-n*(t+1))/(2.0*d)))
  funds = []
  for y in xrange(l1, 1+l2):
    x = sqrt_int(n + d*y*y)
    if x < 0: continue
    funds.append((x, y))
    if (x*x+d*y*y) % n != 0 or (2*x*y) % n != 0: funds.append((-x, y))
  return funds

def pell_bf(d, n, max_x):
  funds = pell_funds_bf(d, n)
  sols = set()
  for x, y in funds: sols.add((abs(x), abs(y)))
  for t, u in pell1(d, 1):
    added = False
    for r, s in funds:
      x = r*t + s*u*d
      y = r*u + s*t
      if abs(x) <= max_x:
        sols.add((abs(x), abs(y)))
        added = True
    if not added: break
  sols = list(sols)
  sols.sort()
  return sols

# Find solutions to a.x^2-b.y^2=c^2
def quad_s(a, b, c, max_x):
  res = []
  for x, y in pell_bf(a*b, a*c, a*max_x):
    x, rem = divmod(x, a)
    if rem == 0: res.append((x, y))
  return res

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
  print "Testing pell4_min..."
  assert pell4_min(13, 1) == (11, 3), "pell4_min failed"
  assert pell4_min(13, -1) == (3, 1), "pell4_min failed"
  print "Testing pell4..."
  assert list(takewhile(lambda (x, _): x < 10000, pell4(13, 1))) == [(11, 3), (119, 33), (1298, 360)], "pell4 failed"
  assert list(takewhile(lambda (x, _): x < 10000, pell4(13, -1))) == [(3, 1), (36, 10), (393, 109), (4287, 1189)], "pell4 failed"
  print pell_funds_bf(13, 108)
  print pell_funds_bf(157, 12)
  print pell_funds_bf(13, 27)

  print pell_bf(13, 108, 10**8)
  print pell_bf(157, 12, 10**8)
  print pell_bf(13, 27, 10**8)
  print quad_s(8, 9, 72, 10**8)
