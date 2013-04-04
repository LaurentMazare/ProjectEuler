def same_side(point_a, point_b, point_x, point_y):
  x_a, y_a = point_a
  x_b, y_b = point_b
  x_x, y_x = point_x
  x_y, y_y = point_y
  x_orth = y_b - y_a
  y_orth = x_a - x_b
  scal_x = (x_x - x_a) * x_orth + (y_x - y_a) * y_orth
  scal_y = (x_y - x_a) * x_orth + (y_y - y_a) * y_orth
  return (scal_x * scal_y >= 0)

def is_in(point_1, point_2, point_3):
  point_0 = (0, 0)
  cond = same_side(point_1, point_2, point_3, point_0)
  cond = cond and same_side(point_1, point_3, point_2, point_0)
  cond = cond and same_side(point_2, point_3, point_1, point_0)
  return cond

x_a = -340
y_a = 495
x_b = -153
y_b = -910
x_c = 835
y_c = -947
pa = (x_a, y_a)
pb = (x_b, y_b)
pc = (x_c, y_c)

result = 0
f = open("triangles.txt", "r")
content = f.readlines()
matrix = []
for line in content:
  x1, y1, x2, y2, x3, y3 = line.rsplit(",")
  result += is_in((int(x1),int(y1)), (int(x2),int(y2)), (int(x3), int(y3)))
print(result)
