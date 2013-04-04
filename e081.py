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
    line.append(0)
  best.append(line)
for i in range(0, size):
  for j in range(0, size):
    if i>0 and j>0:
      the_max = min(best[i-1][j], best[i][j-1])
    elif i > 0:
      the_max = best[i-1][j]
    elif j > 0:
      the_max = best[i][j-1]
    else:
      the_max = 0
    best[i][j] = int(matrix[i][j]) + the_max

print(best[size-1][size-1])

