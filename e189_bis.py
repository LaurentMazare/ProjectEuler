def create_row(n, nb_element):
  res = []
  for j in xrange(0, nb_element):
    res.append(n % 3)
    n /= 3
  return res

cache = {}
def nb_rec(rows, end_row):
  if rows == 1:
    return 1
  key = (rows, end_row)
  if cache.has_key(key):
    return cache[key]
  res = 0
  end_row = create_row(end_row, rows)
  for prev_row in xrange(0, 3 ** (rows-1)):
    prev_res = nb_rec(rows-1, prev_row)
    prev_row = create_row(prev_row, rows-1)
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
  return sum(nb_rec(rows, end_row) for end_row in xrange(0, 3 ** rows))

print nb_triangles(8)
