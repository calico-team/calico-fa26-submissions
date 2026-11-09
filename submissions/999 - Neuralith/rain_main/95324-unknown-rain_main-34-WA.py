
import sys
from bisect import bisect_left, bisect_right

def solve():
    data = iter(sys.stdin.buffer.read().split())
    t = int(next(data))
    results = []

    for _ in range(t):
        n = int(next(data))
        k = int(next(data))

        groups = {}

        for _ in range(n):
            x = int(next(data))
            y = int(next(data))
            z = int(next(data))
            d = next(data).decode()

            s = x + y
            if s not in groups:
                groups[s] = []

            groups[s].append((x, z, d))

        blocked = 0

        for drones in groups.values():
            if len(drones) < 2:
                continue

            east = sorted(set(x for x, z, d in drones if d == 'E'))
            north = sorted(set(x for x, z, d in drones if d == 'N'))

            if not east or not north:
                continue

            be = [0] * (len(east) + 1)
            bn = [0] * (len(north) + 1)

            points = sorted(drones, key=lambda p: -p[1])

            queries = []

            for x, z, d in drones:
                if d == 'E':
                    queries.append((z, 'N', x + 1, x + k))
                else:
                    queries.append((z, 'E', x - k, x - 1))

            queries.sort(key=lambda q: -q[0])

            def update(bit, pos):
                while pos < len(bit):
                    bit[pos] += 1
                    pos += pos & -pos

            def prefix(bit, pos):
                total = 0
                while pos > 0:
                    total += bit[pos]
                    pos -= pos & -pos
                return total

            def range_sum(bit, coords, lo, hi):
                left = bisect_left(coords, lo)
                right = bisect_right(coords, hi)
                return prefix(bit, right) - prefix(bit, left)

            p = 0

            for z, direction, lo, hi in queries:

                while p < len(points) and points[p][1] > z:
                    x, height, d = points[p]

                    if d == 'E':
                        pos = bisect_left(east, x) + 1
                        update(be, pos)
                    else:
                        pos = bisect_left(north, x) + 1
                        update(bn, pos)

                    p += 1

                if direction == 'E':
                    blocked += range_sum(be, east, lo, hi)
                else:
                    blocked += range_sum(bn, north, lo, hi)

        results.append(str(n * k - blocked))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve()
