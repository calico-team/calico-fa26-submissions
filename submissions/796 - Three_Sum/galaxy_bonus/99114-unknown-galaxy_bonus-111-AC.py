import sys
def my_work():
  tokens = sys.stdin.buffer.read().split()
  if not tokens:
    return
  ptr = 0
  total_tests = int(tokens[ptr])
  ptr += 1
  results = []
  for _ in range(total_tests):
    rows = int(tokens[ptr])
    cols = int(tokens[ptr + 1])
    queries = int(tokens[ptr + 2])
    ptr += 3
    grid_data = b"".join(tokens[ptr : ptr + rows])
    ptr += rows
    parent_list = list(range(rows * cols))
    def find_root(node):
      root = node
      while parent_list[root] != root:
        root = parent_list[root]
      curr = node
      while parent_list[curr] != root:
        next_node = parent_list[curr]
        parent_list[curr] = root
        curr = next_node
      return root
    def connect_nodes(a, b):
      root_a = find_root(a)
      root_b = find_root(b)
      if root_a != root_b:
        parent_list[root_a] = root_b
    red_val = ord(b"R")
    blue_val = ord(b"B")
    for r in range(rows):
      row_base = r * cols
      for c in range(cols):
        curr_idx = row_base + c
        cell1 = grid_data[curr_idx]

        if c + 1 < cols:
          cell2 = grid_data[curr_idx + 1]
          is_rb_br = (cell1 == red_val and cell2 == blue_val) or (
              cell1 == blue_val and cell2 == red_val
          )
          if not is_rb_br:
            connect_nodes(curr_idx, curr_idx + 1)

        if r + 1 < rows:
          cell2 = grid_data[curr_idx + cols]
          is_rb_br = (cell1 == red_val and cell2 == blue_val) or (
              cell1 == blue_val and cell2 == red_val
          )
          if not is_rb_br:
            connect_nodes(curr_idx, curr_idx + cols)

    for _ in range(queries):
      start_r = int(tokens[ptr])
      start_c = int(tokens[ptr + 1])
      end_r = int(tokens[ptr + 2])
      end_c = int(tokens[ptr + 3])
      ptr += 4

      start_node = start_r * cols + start_c
      end_node = end_r * cols + end_c

      is_connected = find_root(start_node) == find_root(end_node)
      results.append("YES" if is_connected else "NO")

  sys.stdout.write("\n".join(results) + "\n")
if __name__ == "__main__":
  my_work()