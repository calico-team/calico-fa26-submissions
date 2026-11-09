import collections
import sys


def main():
  input_data = sys.stdin.read().split()
  if not input_data:
    return

  iterator = iter(input_data)
  T = int(next(iterator))
  results = []

  for _ in range(T):
    N = int(next(iterator))
    R = int(next(iterator))

    recharging = collections.deque()
    available = 2
    possible = True

    for _ in range(N):
      a = int(next(iterator))

      # Process recharges up to the current request timestamp 'a'
      while recharging and recharging[0] <= a:
        recharging.popleft()
        available += 1
        if available > 2:
          available = 2

      # Check if a smoke charge is available
      if available > 0:
        available -= 1
        # Start recharging this used charge sequentially
        if not recharging:
          recharging.append(a + R)
        else:
          recharging.append(recharging[-1] + R)
      else:
        possible = False
        # If impossible, we still need to consume the remaining inputs for this testcase!
        # But wait, in a contest, breaking early means we must consume the rest of `A` values.
        # Let's consume the rest of the N integers for this test case to keep the iterator in sync.
        for _ in range(_ + 1, N):
          next(iterator)
        break

    results.append("YES" if possible else "NO")

  sys.stdout.write("\n".join(results) + "\n")


if __name__ == "__main__":
  main()