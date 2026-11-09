import sys
def its_iqrafarooq():
  all_data = sys.stdin.buffer.read().split()
  if not all_data:
    return

  index = 0
  testcases = int(all_data[index])
  index += 1

  answers = []

  for _ in range(testcases):
    r_count = int(all_data[index])
    c_count = int(all_data[index + 1])
    q_count = int(all_data[index + 2])
    index += 3

    grid_bytes = b"".join(all_data[index : index + r_count])
    index += r_count

    parents = list(range(r_count * c_count))

    def find_test(node):
      head_node = node
      while parents[head_node] != head_node:
        head_node = parents[head_node]
      curr = node
      while parents[curr] != head_node:
        next_node = parents[curr]
        parents[curr] = head_node
        curr = next_node
      return head_node

    def u_sets(a, b):
      head_a = find_test(a)
      head_b = find_test(b)
      if head_a != head_b:
        parents[head_a] = head_b

    red_char = ord(b"R")
    blue_char = ord(b"B")

    for r in range(r_count):
      row_base = r * c_count
      for c in range(c_count):
        curr_idx = row_base + c
        cell_1 = grid_bytes[curr_idx]

        if c + 1 < c_count:
          cell_2 = grid_bytes[curr_idx + 1]
          is_rb_br = (cell_1 == red_char and cell_2 == blue_char) or (
              cell_1 == blue_char and cell_2 == red_char
          )
          if not is_rb_br:
            u_sets(curr_idx, curr_idx + 1)

        if r + 1 < r_count:
          cell_2 = grid_bytes[curr_idx + c_count]
          is_rb_br = (cell_1 == red_char and cell_2 == blue_char) or (
              cell_1 == blue_char and cell_2 == red_char
          )
          if not is_rb_br:
            u_sets(curr_idx, curr_idx + c_count)

    for _ in range(q_count):
      start_r = int(all_data[index])
      start_c = int(all_data[index + 1])
      end_r = int(all_data[index + 2])
      end_c = int(all_data[index + 3])
      index += 4

      start_work = start_r * c_count + start_c
      end_node = end_r * c_count + end_c

      is_tested = find_test(start_work) == find_test(end_node)
      answers.append("YES" if is_tested else "NO")

  sys.stdout.write("\n".join(answers) + "\n")

if __name__ == "__main__":
  its_iqrafarooq()