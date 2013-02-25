from math import exp, sqrt
def h(x, y):
  return (5000-0.005*(x*x+y*y+x*y)+12.5*(x+y)) * exp(-abs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7))

def dh_dx(x, y): return (h(x+1e-6, y) - h(x-1e-6, y)) / 2e-6

def bis(f, lo, up):
  f_lo, f_up = f(lo), f(up)
  while up - lo > 1e-10:
    mid = (lo + up) / 2
    f_mid = f(mid)
    if f_mid < 0: up, f_up = mid, f_mid
    else: lo, f_lo = mid, f_mid
  return (lo+up) / 2

# Find fmin by looking at the highest point on the bottom side (xmin, 0, fmin)
xmin = bis(lambda x: dh_dx(x, 0), 0.0, 1600.0)
fmin = h(xmin, 0.0)
print xmin, fmin

# Then follow the contour on the right up to a point where the tangent could go to B'
# After that do the same on the left up to a point where the tangent could go to A'
# For that, use the symetry around the y =  line to handle the bisection correctly
def walk(target_x, target_y, step):
  d = 0.0
  prev_x, prev_y, prev_tan, alpha = xmin, 0.0, None, xmin
  while True:
    alpha += step # Look for contour on the line y = alpha - x
    x = bis(lambda x: h(x, alpha-x) - fmin, prev_x-5, prev_x+5)
    y = alpha - x
    dy_dx = (y - prev_y) / (x - prev_x)
    # tan is the distance between the target and the point (target_x, y) on the tangent 
    tan = y + dy_dx * (target_x - x) - target_y
    if prev_tan != None and prev_tan * tan < 0 and abs(tan) < 100:
      print "Tangent (%.2f, %.2f) -> (%.2f, %.2f)" % (x, y, target_x, target_y)
      return d + sqrt((prev_x-target_x)*(prev_x-target_x)+(prev_y-target_y)*(prev_y-target_y))
    d += sqrt((prev_x-x)*(prev_x-x) + (prev_y-y)*(prev_y-y))
    prev_x, prev_y, prev_tan = x, y, tan

print "%.3f" % (walk(200, 200, -1.0) + walk(1400, 1400, 1.0))
