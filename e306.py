nb_config = 10 ** 6
nb = 3 # 1, 15, 35
for i in xrange(2, nb_config + 1):
  if i % 34 in [5, 9, 21, 25, 29]: nb+=1
print nb_config - nb
