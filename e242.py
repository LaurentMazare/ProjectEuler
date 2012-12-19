# Easy to spot pattern after generating the values for
# the first hundredth x
def s(x):
  x = 1 + (x-1) / 4
  nb = 0
  res = 0
  while x != 0:
    if x % 2 == 1: res = 3**nb + 2*res
    nb += 1
    x /= 2
  return res
print s(10**12)
