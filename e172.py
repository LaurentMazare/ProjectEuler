cache = {}
def nb(first_digit, nb_digits, digits):
  if digits[first_digit] == 0:
    return 0
  if nb_digits == 1:
    return 1
  digits_key = digits.values()
  digits_key.sort()
  key = str((first_digit, nb_digits, digits_key))
  if cache.has_key(key):
    return cache[key]
  digits[first_digit] -= 1
  res = 0
  for i in range(0, 10):
    res += nb(i, nb_digits-1, digits.copy())
  cache[key] = res
  return res

digits = {}
for i in range(0, 10):
  digits[i] = 3
res = 0
for i in range(1, 10):
  res += nb(i, 18, digits.copy())
print res
