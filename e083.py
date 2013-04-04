max81 = 500000
f = open("matrix.txt", "r")
content = f.readlines()
matrix = []
for line in content:
  matrix.append(line.rsplit(","))
size=len(matrix)
#best = zeros([size, size], Int)
best = []
for i in range(0, size):
  line = []
  for j in range(0, size):
    line.append(max81)
  best.append(line)
best[0][0] = int(matrix[0][0])

k = 0
the_range = range(0, size)
while k < 200:
  k += 1
  for i in the_range:
    for j in the_range:
      the_max = max81
      if i>0:
        the_max = min(the_max, best[i-1][j])
      if i<79:
        the_max = min(the_max, best[i+1][j])
      if j>0:
        the_max = min(the_max, best[i][j-1])
      if j<79:
        the_max = min(the_max, best[i][j+1])
      best[i][j] = min(best[i][j], int(matrix[i][j]) + the_max)

print(best[size-1][size-1])
