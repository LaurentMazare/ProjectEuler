# Matrix based solution using fast exponentiation.
def fact(x): return 1 if x == 0 else x * fact(x-1)
def c(n, p): return fact(n)/fact(p)/fact(n-p)
# Very inefficient matrix multiplication/exponentiation, would be better to use numpy
def multm(x, y, mod):
  nb_elts = len(x)
  res = [[0] * nb_elts for _ in xrange(nb_elts)]
  for i in xrange(nb_elts):
    for j in xrange(nb_elts):
      tmp = 0
      for k in xrange(nb_elts): tmp += x[i][k] * y[k][j]
      res[i][j] = tmp % mod
  return res

def multv(x, v, mod):
  nb_elts = len(x)
  res = [0] * nb_elts
  for i in xrange(nb_elts):
    tmp = 0
    for k in xrange(nb_elts): tmp += x[i][k] * v[k]
    res[i] = tmp % mod
  return res

def powm(x, n, mod):
  if n == 1: return x
  if n & 1: return multm(x, powm(x, n-1, mod), mod)
  x = powm(x, n/2, mod)
  return multm(x, x, mod)

# A config is a tuple (n, n1, n2, gap) where:
# - n is the number of frogs that are stopped at the current cell
# - n1 is the number of frogs jumping across the current cell that didn't jump across the previous cell
# - n2 is the number of frogs jumping across the current cell that *did* jump across the previous cell
# - gap is True if we haven't created any gap yet, false otherwise.
# We build a transition matrix giving the number of possible ways to go from one config
# to another config, then use modular exponentiation on it.
def F(iters, length, mod):
  iters *= 2 # Because trips are *with* return
  state_ids, cid = {}, 0
  for n in xrange(0, 1+iters):
    for n1 in xrange(0, 1+iters - n):
      n2 = iters - n - n1
      state_ids[(n, n1, n2, True)], state_ids[(n, n1, n2, False)], cid = cid, cid + 1, cid + 2
  nb_states, init_id2, init_id1 = len(state_ids), state_ids[(iters, 0, 0, False)], state_ids[(iters, 0, 0, True)]
  trans = [[0] * nb_states for _ in xrange(nb_states)]
  for (n_1, n1_1, n2_1, gap_1), idx1 in state_ids.iteritems():
    if n_1 == 0 and gap_1 == False: continue
    for (n_2, n1_2, n2_2, gap_2), idx2 in state_ids.iteritems():
      if n1_1 < n2_2 or n_1 < n1_2: continue
      if n_1 == 0 and gap_2: continue
      if n_1 != 0 and gap_1 != gap_2: continue
      w = c(n1_1, n2_2) * c(n_1, n1_2)
      # Add one if we can go from state_1 to state_2
      trans[idx1][idx2] = (trans[idx1][idx2] + w) % mod
  startv = [int(i == init_id1 or i == init_id2) for i in xrange(nb_states)]
  trans = powm(trans, length-1, mod)
  resv = multv(trans, startv, mod)
  return resv[init_id1]

print F(10, 10**12, 10**9)
