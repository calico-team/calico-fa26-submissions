import sys


def solve():
  input_data = sys.stdin.read().split()
  if not input_data:
    return

  iterator = iter(input_data)
  T = int(next(iterator))

  for _ in range(T):
    N = int(next(iterator))
    K = int(next(iterator))

    drones = []
    for _ in range(N):
      x = int(next(iterator))
      y = int(next(iterator))
      z = int(next(iterator))
      d = next(iterator)
      drones.append((x, y, z, d))

  # Total possible rainwater without any blockages
    total_water = N * K

 # Let's count blocking events between pairs (i, j) where j blocks i.
    blocked_count = 0

    for i in range(N):
      xi, yi, zi, di = drones[i]
      for j in range(N):
        if i == j:
          continue
        xj, yj, zj, dj = drones[j]

  # Only an East-moving drone and a North-moving drone can cross paths
     # or drones with matching fixed coordinates.
 # Let's check if they can intersect at time t >= 0.
        if di == "E" and dj == "N":
          # xi + t == xj  =>  t = xj - xi
          # yi == yj + t  =>  t = yi - yj
          if xj - xi == yi - yj:
            t = xj - xi
            if 0 <= t < K and zi < zj:
              blocked_count += 1
        elif di == "N" and dj == "E":
          # xi == xj + t  =>  t = xi - xj
          # yi + t == yj  =>  t = yj - yi
          if xi - xj == yj - yi:
            t = xi - xj
            if 0 <= t < K and zi < zj:
              blocked_count += 1
        elif di == dj:
          if di == "E" and yi == yj:
            # Moving east on the same row
            if xi < xj and zi < zj and xj - xi < K:
              blocked_count += K - (xj - xi)
          elif di == "N" and xi == xj:
            # Moving north on the same column
            if yi < yj and zi < zj and yj - yi < K:
              blocked_count += K - (yj - yi)

    print(total_water - blocked_count)

if __name__ == "__main__":
  solve()