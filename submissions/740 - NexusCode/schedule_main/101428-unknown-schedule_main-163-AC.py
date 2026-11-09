import heapq
import sys


def solve(N: int, M: int, K: int, P: list[int]) -> int:
  """Return the maximum number of classes that can be taken across M semesters.

  N: the number of classes
  M: the number of semesters
  K: the maximum number of classes you can take per semester
  P: a prerequisite array for classes 1 to N (0 if there are no prerequisite
  classes)
  """

  children = [[] for _ in range(N + 1)]
  out_deg = [0] * (N + 1)

  for i in range(1, N + 1):
    p = P[i - 1]
    if p != 0:
      children[p].append(i)
      out_deg[p] += 1

  height = [1] * (N + 1)
  queue = [i for i in range(1, N + 1) if out_deg[i] == 0]

  head = 0
  while head < len(queue):
    u = queue[head]
    head += 1
    p = P[u - 1]
    if p != 0:
      if height[u] + 1 > height[p]:
        height[p] = height[u] + 1
      out_deg[p] -= 1
      if out_deg[p] == 0:
        queue.append(p)

  available = []
  for i in range(1, N + 1):
    if P[i - 1] == 0:
      heapq.heappush(available, (-height[i], i))

  total_taken = 0


  for _ in range(M):
    if not available:
      break

    take_count = min(K, len(available))
    taken_this_semester = []

    for _ in range(take_count):
      _, u = heapq.heappop(available)
      taken_this_semester.append(u)

    total_taken += take_count

    for u in taken_this_semester:
      for v in children[u]:
        heapq.heappush(available, (-height[v], v))

    if total_taken == N:
      break

  return total_taken


def main():
  input_data = sys.stdin.read().split()
  if not input_data:
    return

  iterator = iter(input_data)
  T = int(next(iterator))
  for _ in range(T):
    N = int(next(iterator))
    M = int(next(iterator))
    K = int(next(iterator))
    P = [int(next(iterator)) for _ in range(N)]
    print(solve(N, M, K, P))


if __name__ == '__main__':
  main()