from math import *
def fib(n):
  prev, current = 1, 1
  for i in xrange(1, n-1):
    prev, current = current, current + prev
  return current

def fast_c(n, a, b):
  eps = 1e-14
  costs = [(0, 1)]
  current_cost, current_max = min(a, b), 3 if abs(a-b) < eps else 2
  prev_b, where_pb = 0, 0
  while True:
    costs.append((current_cost, current_max))
    cost_a, cost_b, prev_a, prev_b = None, None, None, None
    for (cost, m) in costs:
      with_a, with_b = cost+a, cost+b
      if with_a <= current_cost * (1 + eps): prev_a, where_pa = with_a, m
      if with_b <= current_cost * (1 + eps): prev_b, where_pb = with_b, m
      if cost_a == None and with_a > current_cost: cost_a, where_a = with_a, m
      if cost_b == None and with_b > current_cost: cost_b, where_b = with_b, m
    if abs(1 - cost_b / cost_a) < eps:
      current_cost = max(cost_a, cost_b)
      current_max = where_a + where_b + 1
    elif cost_a < cost_b:
      current_cost = max(cost_a, prev_b)
      current_max = where_a + where_pb + 1
    else:
      current_cost = max(prev_a, cost_b)
      current_max = where_pa + where_b + 1
    if current_max >= n: return current_cost

print "%.8f" % sum([fast_c(10**12, sqrt(k), sqrt(fib(k))) for k in range(1, 31)])

