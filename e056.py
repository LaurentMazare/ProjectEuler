max_sum = 0
for a in range(100):
  for b in range(100):
    sum = 0
    for c in str(a ** b):
      sum = sum + int(c)
    if sum > max_sum:
      max_sum = sum

print max_sum
