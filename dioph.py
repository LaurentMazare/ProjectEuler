def gcd(x, y): return x if y == 0 else gcd(y, x % y)

def extended_gcd(a, b):
  if b == 0: return (1, 0)
  q, r = div_mod(a, b)
  s, t = extended_gcd(b, r)
  return t, s - q*t

if __name__ == "__main__":
  print "Testing GCD..."
  assert gcd(3, 1) == 1, "GCD failed"
  assert gcd(3, 9) == 3, "GCD failed"
  assert gcd(48, 18) == 6, "GCD failed"
