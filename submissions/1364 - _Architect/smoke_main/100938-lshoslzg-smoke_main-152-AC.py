import collections
import sys


def main():
  input_data = sys.stdin.read().splitlines()
  if not input_data:
    return

  T = int(input_data[0])
  line_idx = 1
  results = []

  for _ in range(T):
    N, R = map(int, input_data[line_idx].split())
    A = list(map(int, input_data[line_idx + 1].split()))
    line_idx += 2

    recharging = collections.deque()
    available = 2
    possible = True

    for a in A:
      while recharging and recharging[0] <= a:
        recharging.popleft()
        available += 1
        if available > 2:
          available = 2

      if available > 0:
        available -= 1
        if not recharging:
          recharging.append(a + R)
        else:
          recharging.append(recharging[-1] + R)
      else:
        possible = False
        break

    results.append("YES" if possible else "NO")

  print("\n".join(results))


if __name__ == "__main__":
  main()