# Very unoptimized code with lots of unproven assumptions. This
# would gain a lot by being rewritten in a compiled language for speed.
max_n = 200000

# First, use a brute-force DP approach to experiment
# Time complexity is O(n^3), space is O(n^2) so won't work for 200000
cache = {}
def c(m, n):
  if n <= m: return 0, None
  if (m, n) in cache: return cache[(m, n)]
  res, where = None, None
  k = n-1
  while k >= m:
    tmp = k + max(c(m, k-1)[0], c(k+1, n)[0])
    if res == None or tmp < res: res, where = tmp, k
    if k == n-1: k -= 2
    elif k == n-3: k -= 4
    else: k -= 8
  cache[(m, n)] = res, where
  return res, where

# The right part (after the pivot) always is a balanced tree with the deepest
# nodes on the left, this has at most two different levels for leafs.  Worst
# cost search is either on the node on the very right or on the node on the
# very right at the deepest level.  Build a function to compute the cost in
# both cases
def right(k, nb):
  if nb == 1: return 0
  if nb == 2: return k+1
  if nb == 3: return k+2
  alpha = 0
  while 2**(alpha+1) - 1 < nb: alpha += 1
  cap = 2 ** alpha
  occ = nb - cap + 1
  root = cap - max(0, cap/2 - occ)
  tmp = right(k, root-1) if occ <= cap / 2 else right(k+root, nb-root)
  return k + root + tmp

def right_bis(k, nb):
  if nb == 1: return 0
  if nb == 2: return k+1
  if nb == 3: return k+2
  alpha = 0
  while 2**(alpha+1) - 1 < nb: alpha += 1
  cap = 2 ** alpha
  occ = nb - cap + 1
  root = cap - max(0, cap/2 - occ)
  return k + root + right_bis(k+root, nb-root)

cs = [0] * (1+max_n)
for n in xrange(1, max_n+1):
  if n <= 20:
    cs[n], where = c(1, n)
  else:
    res, k = None, where + 1
    for k in [k, k-8, k-16, k-32, k-64, k-128, k-256]: # Looks like it has to be a power of 2
      if k < 0: break
      tmp = k + max(cs[k-1], right(k, n-k), right_bis(k, n-k))
      if res == None or tmp < res: res, where = tmp, k
    cs[n] = res
print sum(cs)
