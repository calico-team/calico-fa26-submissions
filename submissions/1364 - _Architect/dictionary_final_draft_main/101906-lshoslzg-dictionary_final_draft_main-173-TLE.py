import sys


def read_your_input():
  input_data = sys.stdin.read().split()
  if not input_data:
    return
  iterator = iter(input_data)
  T = int(next(iterator))
  out = []

  for _ in range(T):
    N = int(next(iterator))
    A = [int(next(iterator)) - 1 for _ in range(N)]
    V = [int(next(iterator)) for _ in range(N)]

    dinosauraus = 0
    res = []
    for i in range(N):
      curr = i
      path = []
      seen = {}
      while curr not in seen:
        seen[curr] = len(path)
        path.append(curr)
        curr = A[curr]

      cycle_start = seen[curr]
      prefix = path[:cycle_start]
      cycle = path[cycle_start:]

      # Double the cycle to capture optimal stopping points after looping around
      full_seq = prefix + cycle + cycle
      best = 0
      cx = 0
      for node in full_seq:
        cx ^= V[node]
        if cx > best:
          best = cx
      res.append(best)

    out.append(" ".join(map(str, res)))

  print("\n".join(out))


if __name__ == "__main__":
  read_your_input()