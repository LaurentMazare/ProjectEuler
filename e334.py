t = 123456
def next_t():
  global t
  t = t/2 if t % 2 == 0 else (t/2) ^ 926252
  return (t % 2048) + 1

# Consider that we have q_i beans on cell i
# Let s_0 = sum_i q_i
#     s_1 = sum_i q_i * i
#     s_2 = sum_i q_i * i^2
# Then on each move, s_0 and s_1 are unchanged
#                    s_2 is increased by 2
def sum2(n): return (n*(n+1)*(2*n+1))/6
def fast_f(cfg):
  s0, s1, s2 = sum(cfg), 0, 0
  for idx, qty in enumerate(cfg):
    idx += s0
    s1, s2 = s1 + qty * idx, s2 + qty * idx * idx
  # Find the start point and the empty point using s1
  # This could be found directly without the loop but looping is fast enough :)
  for start in xrange(0, s0):
    toremove = s0 * start + (s0 * (s0 + 1)) / 2 - s1
    if 0 <= toremove < s0: break
  final_s2 = sum2(start+s0) - sum2(start-1) - (start + toremove)**2
  return (final_s2 - s2) / 2

print fast_f([next_t() for _ in xrange(1500)])
