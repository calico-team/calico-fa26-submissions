import heapq
import sys


def solve():
  input_data = sys.stdin.read().split()
  if not input_data:
    return
  iterator = iter(input_data)
  T = int(next(iterator))
  out = []
  for _ in range(T):
    N = int(next(iterator))
    M = int(next(iterator))
    K = int(next(iterator))
    P = [0] + [int(next(iterator)) for _ in range(N)]

    sys.setrecursionlimit(max(2000, N + 50))

    children = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
      if P[i] != 0:
        children[P[i]].append(i)

    height = [0] * (N + 1)

    def compute_height(u):
      h = 1
      for v in children[u]:
        h = max(h, 1 + compute_height(v))
      height[u] = h
      return h

    for i in range(1, N + 1):
      if P[i] == 0:
        compute_height(i)

    avail = []
    for i in range(1, N + 1):
      if P[i] == 0:
        heapq.heappush(avail, (-height[i], i))

    total_taken = 0
    for semester in range(M):
      if not avail:
        break
      today_taken = []
      for _ in range(min(K, len(avail))):
        h_neg, u = heapq.heappop(avail)
        today_taken.append(u)
      total_taken += len(today_taken)
      for u in today_taken:
        for v in children[u]:
          heapq.heappush(avail, (-height[v], v))

    out.append(str(total_taken))

  print("\n".join(out))


if __name__ == "__main__":
    solve()