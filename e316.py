import itertools
def solve_linear(eqs):  # Simple Gauss elimination on integer matrixes
  current_eqs = eqs     # Only works on n*n matrix A such that det(A) != 0
  l = len(eqs)
  for i in xrange(1, l):
    next_eqs = []
    for pivot_index, (pivot_line, pivot_value) in enumerate(current_eqs):
      pivot_elt = pivot_line[l-i]
      if pivot_elt != 0:
        for index, (line, value) in enumerate(current_eqs):
          elt = line[l-i] # Generate elt*pivot_line - pivot_elt*line
          if index == pivot_index: continue
          f = lambda x, y: elt*x - pivot_elt*y
          current_line = list(itertools.imap(f, pivot_line, line))
          next_eqs.append((current_line, f(pivot_value, value)))
        break
    current_eqs = next_eqs
  return current_eqs[0][1] / current_eqs[0][0][0]

def generate_eq(nb_str, current_i):
  prefix = nb_str[0:current_i]
  left_hand = [0] * len(nb_str)
  for digit in xrange(0, 10):
    current = prefix + str(digit)
    idx = 0
    while current[idx:] != nb_str[:current_i + 1 - idx]: idx += 1
    if current_i+1-idx != len(nb_str): left_hand[current_i+1-idx] -= 1
  left_hand[current_i] += 10
  return (left_hand, 10)

def g(nb):
  nb_str = str(nb)
  eqs = [generate_eq(nb_str, i) for i in xrange(0, len(nb_str))]
  return solve_linear(eqs) + 1 - len(nb_str)

print sum([g(10**16/i) for i in xrange(2, 10**6)])

