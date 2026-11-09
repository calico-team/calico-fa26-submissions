import sys


def solve():
  input_data = sys.stdin.read().split()
  if not input_data:
    return

  phase = input_data[0]
  N = int(input_data[1])

  if phase == "FIRST":
    # Read edges
    edges = []
    idx = 2
    for _ in range(N - 1):
      u = int(input_data[idx])
      v = int(input_data[idx + 1])
      edges.append((u, v))
      idx += 2

    # Build adjacency list
    adj = [[] for _ in range(N + 1)]
    for u, v in edges:
      adj[u].append(v)
      adj[v].append(u)

    # Root at vertex 1, find parents using BFS
    parent = [0] * (N + 1)
    visited = [False] * (N + 1)

    queue = [1]
    visited[1] = True
    head = 0
    while head < len(queue):
      u = queue[head]
      head += 1
      for v in adj[u]:
        if not visited[v]:
          visited[v] = True
          parent[v] = u
          queue.append(v)

    # Construct array A
    A = [0] * (N + 1)
    xorr = 0
    for i in range(2, N + 1):
      A[i] = parent[i]
      xorr ^= A[i]
    A[1] = xorr

    # Output A_1 to A_N
    print(*(A[1:]))

  elif phase == "SECOND":
    A = [0] + [int(x) for x in input_data[2:]]

    missing_idx = -1
    for i in range(1, N + 1):
      if A[i] == -1:
        missing_idx = i
        break

    # Recover the missing value using XOR sum property
    val = 0
    for i in range(1, N + 1):
      if A[i] != -1:
        val ^= A[i]
    A[missing_idx] = val

    # Reconstruct and output the N-1 edges of the tree
    for i in range(2, N + 1):
      print(f"{i} {A[i]}")


if __name__ == "__main__":
  solve()
