# Simple formula for the expected number of cut rounds:
# Let e(x) be the expected number of cuts when a proportion x of
# the pie is remaining, e(x) = 0 for x < F
# Then x*x*e''(x) + 4*x*e'(x) = 2
# Which can be solved as e(x) = a / x^3 + b + 2*ln(x)/3
# with boundary conditions e(F) = 1, e'(F) = 0
from math import log
def e(f, x):
  a = 2.0 * f ** 3 / 9.0
  b = 1 - 2.0 / 9.0 - 2.0 * log(f) / 3
  return a / x ** 3 + b + 2 * log(x) / 3

print "%.10f\n%.10f\n%.10f\n" % (e(1.0/2.0, 1), e(1.0/7.5, 1), e(1.0/40.0, 1))
