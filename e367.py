import itertools
from fractions import Fraction
nb_perm, nb_elts = 3, 11
f_zero, f_one = Fraction(0, 1), Fraction(1, 1)

def list_of_cycles(c):
  res, idx = [0] * nb_elts, 0
  for l, nb in enumerate(c):
    for _ in xrange(0, nb):
      res[idx] = idx + l
      idx += 1
      for _ in xrange(0, l):
        res[idx] = idx - 1
        idx += 1
  return res

def cycles_of_list(perm):
  res, seen = [0] * nb_elts, [False] * nb_elts
  for p in perm:
    if seen[p]: continue
    pp, l = p, 0
    while l == 0 or pp != p:
      l += 1
      seen[pp] = True
      pp = perm[pp]
    res[l-1] += 1
  return res

def lin_solve(eqs): # Simple Gaussian elimination solving
  nb_var = len(eqs)
  for idx_var in xrange(0, nb_var):
    current_max, where_max = f_zero, None
    for idx in xrange(idx_var, nb_var):
      if current_max < abs(eqs[idx][idx_var]): current_max, where_max = abs(eqs[idx][idx_var]), idx
    eqs[idx_var], eqs[where_max] = eqs[where_max], eqs[idx_var]
    l_var = eqs[idx_var][idx_var]
    for idx in xrange(idx_var+1, nb_var):
      l_idx = eqs[idx][idx_var]
      eqs[idx] = list(itertools.imap(lambda x, y: x * l_idx / l_var - y, eqs[idx_var], eqs[idx]))
  res = [None] * nb_var
  for idx_var in reversed(xrange(0, nb_var)):
    res[idx_var] = -eqs[idx_var][nb_var]
    for idx in xrange(idx_var+1, nb_var):
      res[idx_var] -= eqs[idx_var][idx] * res[idx]
    res[idx_var] /= eqs[idx_var][idx_var]
  return res

cycles_nb = {}
for perm in itertools.permutations(xrange(0, nb_elts)):
  key = tuple(cycles_of_list(perm))
  cycles_nb[key] = cycles_nb.get(key, 0) + 1
cycles_of_int, int_of_cycles = [], {}
for cycles, _ in cycles_nb.iteritems():
  int_of_cycles[cycles] = len(cycles_of_int)
  cycles_of_int.append(cycles)

all_ops = map(lambda x: (x, sorted(x)), itertools.permutations(xrange(0, nb_elts), nb_perm))
eqs, nb_var = [], len(cycles_of_int)
for cycle_idx, cycles in enumerate(cycles_of_int):
  eq = [f_zero] * nb_var
  eq[cycle_idx] = f_one
  if cycles[0] != nb_elts:
    perm = list_of_cycles(cycles)
    for ops, ops_sorted in all_ops:
      next_perm = list(perm)
      for idx, op in enumerate(ops): next_perm[op] = perm[ops_sorted[idx]]
      key = int_of_cycles[tuple(cycles_of_list(next_perm))]
      eq[key] -= f_one / len(all_ops)
  eqs.append(eq + [f_zero if cycles[0] == nb_elts else -f_one])

e = lin_solve(eqs)
p = sum([nb * e[int_of_cycles[c]] for c, nb in cycles_nb.iteritems()])
print float(p/sum(cycles_nb.values()))

