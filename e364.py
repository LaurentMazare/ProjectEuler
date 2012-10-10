from array import array
modF = 100000007

facts = [1]
for i in xrange(1, 10**6): facts.append((i*facts[-1]) % modF)
inv_facts = map(lambda x: pow(x, modF-2, modF), facts) # As modF is prime, easy way to obtain its inverse
facts = array('l', facts)
inv_facts = array('l', inv_facts)

def fact(x, y = 0): return (facts[x] * inv_facts[y]) % modF
def all_combs(n):
  res = 0
  for left in [True, False]: # Is the left seat occupied ?
    for right in [True, False]: # Is the right seat occupied ?
      to_fill = n - int(not left) - int(not right)
      for nb_1 in xrange(0, (1 + to_fill) / 2): # Number of empty seat with the two adjacent seat occupied
        rest = to_fill - 2 * nb_1 - 1
        if rest % 3 != 0: continue
        nb_2 = rest / 3 # Number of two adjacent empty seats with occupied seats on both sides
        nb = to_fill - 2 * nb_2 - nb_1 # Number of occupied seats
        nb_2_ = nb_2 + int(not left) + int(not right)
        res = (res + fact(nb_1+nb_2, nb_1) * fact(nb) * fact(nb_2_) * fact(nb_1+nb_2, nb_2) * pow(2, nb_2, modF)) % modF
  return res

print all_combs(4)
print all_combs(10)
print all_combs(1000)
print all_combs(10**6)
