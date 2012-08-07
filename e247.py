from math import sqrt
import collections # for deque

def squares(x_int, y_int, min_x, x_float, y_float):
  res = set()
  tasks = collections.deque()
  tasks.append((x_int, y_int, x_float, y_float))
  while len(tasks):
    (x_int, y_int, x_float, y_float) = tasks.pop()
    delta = (x_float + y_float) ** 2 - 4.0 * (x_float * y_float - 1.0)
    x = (- x_float - y_float + sqrt(delta)) * 0.5
    res.add((x_int, y_int, x))
    if x > min_x:
      tasks.append((x_int, y_int+1, x_float, y_float+x))
      tasks.append((x_int+1, y_int, x_float+x, y_float))
  return res

all_squares = list(squares(0, 0, 0.0005, 1.0, 0.0))
all_squares = sorted(all_squares, key = lambda x: -x[2])
print len(all_squares)
for i, elem in enumerate(all_squares):
  if elem[0] == 3 and elem[1] == 3:
    print (i+1, elem)

