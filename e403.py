# Use wxmaxima to handle the calculus:
# delta: a**2+4*b;
# x1: (a-sqrt(delta))/2;
# x2: (a+sqrt(delta))/2;
# area: a/2*(x2**2-x1**2)+b*(x2-x1)-(x2**3-x1**3)/3;
# ratsimp(area);
# This gives that the area is rational iff delta is a perfect square.
# Let's call s the square root of delta,
# sss: factor(sum(a*k+b-k*k+1, k, x1, x2)), simpsum=true;
# After that, instead of looping on a and s, we loop on the intersection
# of the parabol and the line: x = (a-s)/2, y = (a+s)/2
from math import *
def sss(s): return ((s+1)*(s*s-s+6))/6

def sum_sss(x1, x2, y1, y2): # sum_{x=x1..x2} sum_{y=y1..y2} sss(y-x)
  if x2 < x1 or y2 < y1: return 0
  return ((x2-x1+1)*(y2-y1+1)*(y2**3+y1*y2**2-2*x2*y2**2-2*x1*y2**2+y2**2+y1**2*y2-2*x2*y1*y2-2*x1*y1*y2+2*x2**2*y2+2*x1*x2*y2+2*x1**2*y2-2*x1*y2+10*y2+y1**3-2*x2*y1**2-2*x1*y1**2-y1**2+2*x2**2*y1+2*x1*x2*y1+2*x2*y1+2*x1**2*y1+10*y1-x2**3-x1*x2**2-x2**2-x1**2*x2-10*x2-x1**3+x1**2-10*x1+24))/24

# Fast version of s2, sum with all three constraints by separating
# three main regions...
def s3(n):
  sqrt_n = int(sqrt(n))
  res = 2*sum([sum_sss(x, x, x, min(n/x if x != 0 else n, n-x)) for x in xrange(0, 1+sqrt_n)])-sss(0)
  res += sum_sss(-sqrt_n, -1, 1, sqrt_n) # Square below hyperbola on the left-up corner
  # Below hyperbola but outside of the square.
  res += 2 * sum([sum_sss(x, x, sqrt_n+1, n/-x) for x in xrange(-sqrt_n, 0)])
  return res

print s3(10**12) % 10**8
