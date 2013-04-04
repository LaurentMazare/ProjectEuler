import itertools

def gen_square(dice1, dice2):
  set1 = set(dice1)
  set2 = set(dice2)
  if 6 in set1:
    set1.add(9)
  if 6 in set2:
    set2.add(9)
  if 9 in set1:
    set1.add(6)
  if 9 in set2:
    set2.add(6)
  for x in range(1, 10):
    sq = x * x
    ch1 = sq / 10
    ch2 = sq % 10
    if not ((ch1 in set1 and ch2 in set2) or (ch2 in set1 and ch1 in set2)):
      return False
  return True

numbers = range(0, 10)
nb = 0
for dice1 in itertools.combinations(numbers, 6):
  for dice2 in itertools.combinations(numbers, 6):
    if dice1 <= dice2 and gen_square(dice1, dice2):
      nb += 1
print nb
