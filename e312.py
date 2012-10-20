def phi(n): # Euler Totient
  output = n
  if n % 2 == 0: output -= output / 2
  while n % 2 == 0: n /= 2
  i = 3
  while i * i <= n:
    if n % i == 0: output -= output / i
    while n % i == 0: n /= i
    i += 1
  if n > 1: output -= output / n
  return output

# C(n) = 2^(3^(n-2)) * 3^((3^(n-2)-3)/2)
# c(n, 1, mod) = C(n) % mod
# c(n, 2, mod) = C(C(n)) % mod
# c(n, 3, mod) = C(C(C(n))) % mod
def c(n, level, mod):
  if level == 0: return n % mod
  p = phi(mod)
  p2 = pow(3, (c(n, level-1, p) + p - 2) % p, p)
  p3 = (pow(3, (c(n, level-1, phi(2*mod)) + p - 2) % p, p) - 3) / 2
  return pow(2, p2, mod) * pow(3, p3, mod) % mod


mod = 13 ** 8
print c(10**4, 1, mod)
print c(10**4, 3, mod)
