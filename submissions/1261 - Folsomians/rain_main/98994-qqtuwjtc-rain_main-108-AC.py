"""
* Return an integer denoting the amount of rain collected after the Kth nights
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""
from bisect import bisect_left, bisect_right

def solve(N: int, K: int, L: list):
  water_counter = N * K
  north = {}
  for i in L:
    x, y, z, d = i[0], i[1], i[2], i[3]
    if d == "N":
      s = x + y
      if s not in north:
        north[s] = []
      north[s].append(x)
  for s in north:
    north[s].sort()
  for i in L:
    x, y, z, d = i[0], i[1], i[2], i[3]
    if d == "E":
      s = x + y
      if s in north:
        arr = north[s]
        min = x
        max = x + K - 1
        left = bisect_left(arr, min)
        right = bisect_right(arr, max)
        water_counter -= (right - left)
  return water_counter

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()