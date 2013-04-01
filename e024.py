import itertools
import string
for idx, perm in enumerate(itertools.permutations(xrange(0, 10))):
  if idx == 1000000-1:
    print string.join(map(lambda x: str(x), perm), '')
    break
