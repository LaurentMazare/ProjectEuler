from math import *
max_num = 0;
where_max = 0;
for i in range(1, 1001):
  m = 0
  d = 1
  a = int(sqrt(i))
  num = a+1
  den = 1
  if a*a == i: continue
  a_stored = [a]
  while num * num - den * i * den != 1:
    m = d*a - m
    d = (i - m*m) / d
    a = int((sqrt(i)+float(m)) / float(d))
    a_stored.append(a)
    num = a
    den = 1
    for k in reversed(range(0, len(a_stored) - 1)):
      num, den = a_stored[k]*num + den, num
  if num > max_num:
    max_num = num
    where_max = i
print where_max
