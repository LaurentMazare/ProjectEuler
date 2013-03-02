from math import *

phi = (1 + sqrt(5)) / 2
def s(n):
  if n <= 1: return 0, 0, 0
  n_phi = int(n/phi)
  m_phi = n-n_phi-1
  below, above, total = s(n_phi)
  sum_phib = (n_phi*(n_phi+1)*(n_phi-1)) / 3
  sum_bis, sum_bisb = (m_phi * (m_phi+1)) / 2, (m_phi*(m_phi+1)*(m_phi-1)) / 3
  below += (n_phi+2)*sum_bis + sum_bisb + 3*sum_phib/2 - below - total
  above += (n-1)*sum_bis - sum_bisb + sum_phib - total
  return below, above, below + above

#print s(10)[-1]
#print s(10**4)[-1]
print s(10**16)[-1] % (7**10)
