def starts_at(n):
  b, digits, res = 1, 1, 0
  while 10 * b < n:
    res += digits * 9 * b
    b *= 10
    digits += 1
  return res + digits * (n-b)

def nb_digits(n):
  res = 0
  while 0 < n:
    n /= 10
    res += 1
  return res

def starts_with(n, pre):
  if pre == 0: return False
  while pre <= n:
    if n == pre: return True
    n /= 10
  return False

def f(n, k):
  dig_n, dig_k = nb_digits(n), nb_digits(k)
  pos = set([(n, 0)])
  for dig in xrange(0, 1+dig_k):
    for digits in xrange(0, 10**dig):
      for dig_b in xrange(0, 1+dig):
        a, b = divmod(digits, 10**dig_b)
        to_add = a * 10**(dig_b+dig_n) + n * 10**dig_b + b
        pos.add((to_add, nb_digits(a)))
    if len(pos) > k: break
  max_s = max(pos)
  for i in xrange(1, dig_n):
    w1, w2 = divmod(n, 10**i)
    if w2 < 10*(i-1): continue
    dig_w1 = nb_digits(w1)
    str_w2 = str(w2)
    for idx2 in xrange(0, len(str_w2)):
      a = int(str_w2[:idx2]) if 0 < idx2 else 0
      x = a * 10**dig_w1 + w1
      if x <= max_s and starts_with(x+1, w2):
        pos.add((x, nb_digits(a)))
    for dig_a in xrange(0, 1+dig_k):
      x = 0
      for a in xrange(0, 10**dig_a):
        a = w2 * 10**dig_a + a
        x = a * 10**dig_w1 + w1
        if x <= max_s and starts_with(1+x, w2):
          pos.add((x, nb_digits(a)))
        elif max_s < x: break
      if max_s < x: break
  all_pos = list(pos)
  all_pos.sort()
  nb, offset = all_pos[k-1]
  return 1 + starts_at(nb) + offset

print f(12, 12)
print f(7780, 7780)
res = 0
for k in xrange(1, 14):
  tmp_f = f(3**k, 3**k)
  print k, 3**k, tmp_f
  res += tmp_f
print res
