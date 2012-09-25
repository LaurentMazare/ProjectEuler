from array import *

def ee(p, n): # p: probability of infection
  e = array('d', [0.0] * (n+1)) # average optimum number of required tests
  f = array('d', [0.0] * (n+1)) # average optimum number of required tests
                                # knowing that there is at least one sick member in the group
  p1 = [1.0 - (1.0 - p) ** k for k in xrange(0, n+1)] # proba to have at least one sick among k
  p2 = lambda (k, n): p1[k] / p1[n] # proba to have at least one sick in k knowing that there is
                                    # at least one sick in a superset of size n
  for k in xrange(1, n+1):
    if k > 1:
      f[k] = 1 + min([p2((i, k)) * (f[i] + e[k-i]) + (1 - p2((i, k))) * f[k-i] for i in xrange(1, k)])
    e[k] = 1 + min([p1[i] * f[i] + e[k-i] for i in xrange(1, k+1)])
  return e[n]

print ee(0.02, 25)
print "%.6f" % sum([ee(0.01*p, 10000) for p in xrange(1, 51)])
