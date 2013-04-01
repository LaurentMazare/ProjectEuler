f, prev, idx = 1, 1, 2
while True:
  if 1000 <= len(str(f)): break
  f, prev, idx = f+prev, f, idx+1
print idx

