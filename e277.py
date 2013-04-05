seq = "DdDddUUdDD"
low = pow(10, 6)
seq = "UDDDUdddDDUDDddDdDddDDUDDdUUDd"
low = pow(10, 15)
n = len(seq)
start = 1
while True:
  value = start
  ok = True
  for i in range(0, n):
    idx = n - i - 1
    if seq[idx] == 'D':
      value *= 3
    elif seq[idx] == 'U':
      if value % 4 != 2:
        ok = False
        break
      value = (value * 3 - 2) / 4
    elif seq[idx] == 'd':
      if value % 2 == 0:
        ok = False
        break
      value = (value * 3 + 1) / 2
    else:
      print "wronggggg"
  if ok and value > low:
    print value
    break
  start += 1
