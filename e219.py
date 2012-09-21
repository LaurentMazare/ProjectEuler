# This one was quite tough, I generated the cost for n <= 4000 using
# DP then noticed a pattern:
# cost(i) - cost(i-1) is equal to 1, then 2, then 3 and so on and
# it keeps a constant value for longer and longer periods.
# The length of the periods is given by u_n
# where u_1 = u_2 = u_3 = u_4 = 1 and u_n = u_{n-1} + u_{n-4}
# This solves it instantaneously

from array import array
changes = [1, 1, 1, 1]
for i in xrange(0, 100): changes.append(changes[-1]+changes[-4])

target = 10 ** 9
total = 0
incr = 1
prev_x = 1
for x in changes:
  if target < x:
    total += incr * (target - prev_x)
    break
  else: total += incr * (x - prev_x)
  incr += 1
  prev_x = x
print total
