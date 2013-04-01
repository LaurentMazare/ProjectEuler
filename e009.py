done = False
for p in xrange(1, 100):
  for q in xrange(1, p):
    a = p*p - q*q
    b = 2*p*q
    c = p*p + q*q
    if a + b + c == 1000:
      print a * b * c
      done = True
      break
  if done: break
