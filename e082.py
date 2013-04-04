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
k = 0
the_range = range(0, size)
for i in the_range:
  best[i][0] = int(matrix[i][0])

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
      best[i][j] = min(best[i][j], int(matrix[i][j]) + the_max)

min_path = max81
for i in the_range:
  min_path = min(best[i][size-1], min_path)
print(min_path)
