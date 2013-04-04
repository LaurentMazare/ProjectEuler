
cache = {}
def nb(start, a, un, zero, length):
  if length == 0 and start == False and a == True and un == True and zero == True:
    return 1
  if length == 0:
    return 0
  if cache.has_key((start, a, un, zero, length)):
    return cache[start, a, un, zero, length]
  res = 0
  res += 13*nb(False, a, un, zero, length-1)
  res += nb( False, True, un, zero, length-1)
  res += nb( False, a, True, zero, length-1)
  if start == False:
    res += nb( start, a, un, True, length-1)
  if start == True:
    res += nb(start, a, un, zero, length-1)
  cache[start, a, un, zero, length] = res
  return res

print(hex(nb(True, False, False, False, 16)).upper());
