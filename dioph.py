from math import sqrt

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
    print i, p_i, q_i, alpha_i, ">", a_i, b_i, g_i, ir
    if ir != None and ir != i and p_i == p_ir and q_i == q_ir: break
    # Update p_i and q_i for i+1
    p_i = alpha_i * q_i - p_i
    q_i = (d - p_i * p_i) / q_i
    if i > 20: break

if __name__ == "__main__":
  print "Testing GCD..."
  assert gcd(3, 1) == 1, "GCD failed"
  assert gcd(3, 9) == 3, "GCD failed"
  assert gcd(48, 18) == 6, "GCD failed"
  pqa(11, 108, 13)
  pqa(0, 1, 13)
