# A given rank can be present in the 4 suits, hence there are 2^4 suit configurations.
# For example, 0b1001 will represent that the rank exists in suit 0 and 3.

# A config describes a card set as an array of 16 int. For example:
# [12, 1, 0, ... 0] denotes the config where for 12 ranks, the suit configuration
# is 0 and so these ranks are not in the card set, and for 1 rank, the suit configuration
# is 1 and so this rank exists only for suit 0.
# So the config can be seen as a mapping from suit configurations to the number
# of ranks that have this suit configuration.
def badugi(cfg):
  s = [[], [], [], []]
  idx = 0
  for suits, nb in enumerate(cfg):
    for i in xrange(0, nb):
      for j in xrange(0, 4):
        if suits & (1 << j): s[j].append(idx)
      idx += 1
  for c0 in s[0]:
    for c1 in s[1]:
      if c0 == c1: continue
      for c2 in s[2]:
        if c2 == c0 or c2 == c1: continue
        for c3 in s[3]:
          if c3 == c0 or c3 == c1 or c3 == c2: continue
          return True
  return False

def a(n, p): return 1 if 0 == p else n * a(n-1, p-1)
def fact(x): return 1 if x == 0 else x * fact(x-1)

# Then the f function below implements a simple DP algorithm to solve the problem
cache = {}
def f(n, nb_cards, cfg):
  key = n, nb_cards, tuple(cfg)
  if key in cache: return cache[key]
  res = 0
  if badugi(cfg): res = a(52-nb_cards, n)
  elif n > 0:
    for suits, nb in enumerate(cfg):
      if nb == 0: continue
      for s in xrange(0, 4):
        if not (suits & (1 << s)):
          new_suits = suits | (1 << s)
          cfg[suits], cfg[new_suits] = cfg[suits]-1, cfg[new_suits]+1
          res += nb * f(n-1, nb_cards+1, cfg)
          cfg[suits], cfg[new_suits] = cfg[suits]+1, cfg[new_suits]-1
  cache[key] = res
  return res

print sum([f(i, 0, [13] + [0] * 15) / fact(i) for i in xrange(4, 14)])
