# Iterator to generate all the vectors of size nb_elements
# which elements are in [0, 1, 2]
def gen_rows(nb_element):
  for i in xrange(0, 3 ** nb_element):
    n = i
    tmp_res = []
    for j in xrange(0, nb_element):
      tmp_res.append(n % 3)
      n /= 3
    yield tmp_res

cache = {}
def nb_rec(rows, end_row):
  if rows == 1:
    return 1
  key = (rows, "".join(map(lambda x: str(x), end_row)))
  if cache.has_key(key):
    return cache[key]
  res = 0
  for prev_row in gen_rows(rows-1):
    prev_res = nb_rec(rows-1, prev_row)
    for index in xrange(0, rows-1):
      if prev_row[index] == end_row[index] and prev_row[index] == end_row[index+1]: # 3 Neighbors have the same color
        prev_res *= 2 # Two possibilities for the inside color
      elif prev_row[index] == end_row[index] or prev_row[index] == end_row[index+1] or end_row[index] == end_row[index+1]: #2 Neighbors have the same color
        prev_res *= 1 # One possibility
      else:
        prev_res = 0
        break
    res += prev_res
  cache[key] = res
  return res

def nb_triangles(rows):
  return sum(nb_rec(rows, end_row) for end_row in gen_rows(rows))

print nb_triangles(8)
