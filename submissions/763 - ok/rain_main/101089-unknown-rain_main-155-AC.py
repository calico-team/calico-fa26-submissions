import sys
from collections import defaultdict
from bisect import bisect_right

def solve():
    input = iter(sys.stdin.buffer.read().split())
    t = int(next(input))
    results = []

    for _ in range(t):
        n = int(next(input))
        k = int(next(input))

        north = defaultdict(list)
        east = []

        for _ in range(n):
            x = int(next(input))
            y = int(next(input))
            z = int(next(input))
            d = next(input)

            s = x + y

            if d == b'E':
                east.append((x, s))
            else:
                north[s].append(x)

        for arr in north.values():
            arr.sort()

        lost = 0

        for x, s in east:
            arr = north.get(s)

            if arr:
                lost += (
                    bisect_right(arr, x + k - 1)
                    - bisect_right(arr, x)
                )

        results.append(str(n * k - lost))

    sys.stdout.write('\n'.join(results))


if __name__ == "__main__":
    solve()