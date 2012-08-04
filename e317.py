from math import sqrt
from math import pi

v = 20.0
g = 9.81
y0 = 100.0
v2g = v * v / g
x0 = sqrt(2.0 * v2g * (y0 + 0.5 * v2g))

vol = 2.0 * pi * ((y0 + 0.5 * v2g) * x0 * x0 * 0.5 - 0.5 / v2g * x0 * x0 * x0 * x0 / 4.0)
print "%.4f %.4f" % (x0, vol)
