# Numpy version as the solution, 300x faster than the plain python one :)
import numpy as np
# Matrix based solution using fast exponentiation.
def fact(x): return 1 if x == 0 else x * fact(x-1)
def c(n, p): return fact(n)/fact(p)/fact(n-p)
# Very inefficient matrix multiplication/exponentiation, would be better to use numpy
def powm(x, n, mod):
  if n == 1: return x
  if n & 1: return np.dot(x, powm(x, n-1, mod)) % mod
  x = powm(x, n/2, mod)
  return np.dot(x, x) % mod

# A config is a set (n, n1, n2, gap) where:
# We build a transition matrix giving the number of possible ways to go from one config
# to another config.
def F(iters, length, mod):
  iters *= 2 # Because trips are *with* return
  state_ids, cid = {}, 0
  for n in xrange(0, 1+iters):
    for n1 in xrange(0, 1+iters - n):
      n2 = iters - n - n1
      state_ids[(n, n1, n2, True)], state_ids[(n, n1, n2, False)], cid = cid, cid + 1, cid + 2
  nb_states, init_id2, init_id1 = len(state_ids), state_ids[(iters, 0, 0, False)], state_ids[(iters, 0, 0, True)]
  trans = np.zeros((nb_states, nb_states))
  for (n_1, n1_1, n2_1, gap_1), idx1 in state_ids.iteritems():
    if n_1 == 0 and gap_1 == False: continue
    for (n_2, n1_2, n2_2, gap_2), idx2 in state_ids.iteritems():
      if n1_1 < n2_2 or n_1 < n1_2: continue
      if n_1 == 0 and gap_2: continue
      if n_1 != 0 and gap_1 != gap_2: continue
      w = c(n1_1, n2_2) * c(n_1, n1_2)
      # Add one if we can go from state_1 to state_2
      trans[idx1][idx2] = (trans[idx1][idx2] + w) % mod
  startv = np.array([int(i == init_id1 or i == init_id2) for i in xrange(nb_states)])
  trans = powm(trans, length-1, mod)
  resv = np.dot(trans, startv)
  return int(resv[init_id1] % mod)

mod5 = F(10, 10**12, 5**9) # 10**9 is too large for the matrix multiplication in numpy...
mod2 = F(10, 10**12, 2**9)
i = 0 # Brute force Chinese Remainder Theorem
while True:
  candidate, i = mod5 + 5**9 * i, i+1
  if candidate % 2**9 == mod2:
    print candidate
    break

