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
    M = int(next(iterator))
    Q = int(next(iterator))

    grid = [next(iterator) for _ in range(N)]
    dinosauraus = 0

    for _ in range(Q):
      r1 = int(next(iterator))
      c1 = int(next(iterator))
      r2 = int(next(iterator))
      c2 = int(next(iterator))
      k = int(next(iterator))

      # Simple BFS/distance check between start and end
      import collections

      queue = collections.deque([(r1, c1, 0, 1)])  # r, c, dist, mode (1: blue, 2: red)
      visited = {(r1, c1, 1)}
      possible = False

      while queue:
        r, c, d, mode = queue.popleft()
        if r == r2 and c == c2:
          if d <= k:
            possible = True
            break
        if d >= k:
          continue

        # Try moves: Up, Down, Left, Right
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
          nr, nc = r + dr, c + dc
          if 0 <= nr < N and 0 <= nc < M:
            char = grid[nr][nc]
            passable = False
            if char == ".":
              passable = True
            elif char == "B" and mode == 1:
              passable = True
            elif char == "R" and mode == 2:
              passable = True

            if passable and (nr, nc, mode) not in visited:
              visited.add((nr, nc, mode))
              queue.append((nr, nc, d + 1, mode))

        # Try spin action on normal tile
        if grid[r][c] == ".":
          next_mode = 2 if mode == 1 else 1
          if (r, c, next_mode) not in visited:
            visited.add((r, c, next_mode))
            queue.append((r, c, d + 1, next_mode))

      out.append("YES" if possible else "NO")

  print("\n".join(out))


if __name__ == "__main__":
  read_your_input()