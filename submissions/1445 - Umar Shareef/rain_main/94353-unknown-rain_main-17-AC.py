import sys
from bisect import bisect_left, bisect_right


def solve():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it))
        k = int(next(it))

        # Two drones moving in the same direction never end up in the same
        # cell (same speed, different starts). An east-moving drone and a
        # north-moving drone can share a cell at most once, and when they
        # do, exactly one of them (the lower one) misses that night's rain.
        #
        # East drone i is at (xi + t, yi); north drone j is at (xj, yj + t).
        # They meet exactly when xi + yi == xj + yj, at time t = xj - xi.
        # So group drones by s = x + y and count, inside each group, the
        # pairs (east, north) with 0 <= xj - xi < K.
        groups = {}  # s -> [east xs, north xs]
        for _ in range(n):
            x = int(next(it))
            y = int(next(it))
            int(next(it))  # z never changes who meets whom
            d = next(it).decode()
            g = groups.setdefault(x + y, ([], []))
            if d == 'E':
                g[0].append(x)
            else:
                g[1].append(x)

        blocked = 0
        for east_xs, north_xs in groups.values():
            if not east_xs or not north_xs:
                continue
            east_xs.sort()
            for xj in north_xs:
                # count east xs with xj - (K - 1) <= xi <= xj
                lo = bisect_left(east_xs, xj - k + 1)
                hi = bisect_right(east_xs, xj)
                blocked += hi - lo

        out.append(str(n * k - blocked))

    sys.stdout.write('\n'.join(out))


if __name__ == '__main__':
    solve()
