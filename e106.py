import itertools
def comp(n):
  elements = range(0, n)
  nb_comb = 0
  # We only check comparisons between subsets of size i
  for i in xrange(2, n/2 + 1):
    subsets_i = itertools.combinations(elements, i)
    # Generate all subsets pairs (subset1, subset2)
    for subset1, subset2 in itertools.combinations(subsets_i, 2):
      # Do not consider pairs with a common element
      if len(set(subset1) & set(subset2)) > 0:
        continue
      # Then no test is needed if all elements of subset1 are below their
      # respective elements in subset2 (as both subsets are sorted)
      s1_lower_than_s2 = None
      no_test_needed = True
      for elem1, elem2 in itertools.izip(subset1, subset2):
        if s1_lower_than_s2 == None:
          s1_lower_than_s2 = elem1 < elem2
        elif s1_lower_than_s2 and elem1 > elem2:
          no_test_needed = False
          break
        elif not s1_lower_than_s2 and elem1 < elem2:
          no_test_needed = False
          break
      if not no_test_needed:
        nb_comb += 1
  return nb_comb

print comp(4)
print comp(7)
print comp(12)
