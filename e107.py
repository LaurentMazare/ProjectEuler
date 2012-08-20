import sys
edges = set()
f = open('network.txt')
for i, line in enumerate(f):
  line_split = line.replace("\r\n","").split(",")
  for j, edge in enumerate(line_split):
    if edge != "-":
      edges.add((int(edge), min(i, j), max(i, j)))
f.close()
edges = list(edges)
edges.sort()

total_weight = sum(map(lambda x: x[0], edges))
      
cache = {}
def aux(nodes, edge_list, current_sum, current_max):
  if len(nodes) == 40:
    return current_sum
  key = str(nodes) + str(edge_list)
  if cache.has_key(key):
    return cache[key]
  res = current_max
  for edge_index, (w, start, end) in enumerate(edges):
    if not edge_index in edge_list and current_sum + w < res:
      start_in = start in nodes
      end_in = end in nodes
      if (start_in or end_in) and not (start_in and end_in):
        node = start if end_in else end
        tmp_nodes = set(nodes)
        tmp_nodes.add(node)
        tmp_sum = aux(tmp_nodes, edge_list + [edge_index], current_sum + w, res)
        if tmp_sum < res:
          print total_weight - tmp_sum
          res = tmp_sum
  cache[key] = res
  return res

print aux(set([0]), [], 0, 10 ** 10)
