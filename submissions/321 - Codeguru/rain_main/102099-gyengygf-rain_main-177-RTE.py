import sys
from bisect import bisect_left, bisect_right


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0

    num_tests = int(data[pos]); pos += 1
    results = []

    for _ in range(num_tests):
        n = int(data[pos])
        k = int(data[pos + 1])
        pos += 2

        # Group drone x-coordinates by their (x + y) diagonal.
        # Drones sharing the same diagonal are the only ones that can collide,
        # so we bucket them accordingly.
        east_by_diag = {}   # x + y -> [x, ...] for east-facing drones
        north_by_diag = {}  # x + y -> [x, ...] for north-facing drones

        for _ in range(n):
            x = int(data[pos])
            y = int(data[pos + 1])
            direction = data[pos + 3]
            pos += 4

            diag = x + y
            if direction == b'E':
                east_by_diag.setdefault(diag, []).append(x)
            else:
                north_by_diag.setdefault(diag, []).append(x)

        # Count collisions. For each north drone and each east drone on the
        # same diagonal, they collide iff 1 <= xE - xN <= k - 1, i.e. the east
        # drone starts between 1 and k-1 units to the right of the north drone.
        lost = 0
        for diag, north_xs in north_by_diag.items():
            east_xs = east_by_diag.get(diag)
            if not east_xs:
                continue

            east_xs.sort()
            for xn in north_xs:
                # Number of east drones with x in [xn - k + 1, xn - 1].
                low = bisect_left(east_xs, xn - k + 1)
                high = bisect_right(east_xs, xn - 1)
                lost += high - low

        # Total drones minus one lost per collision.
        results.append(str(n * k - lost))

    sys.stdout.write("\n".join(results) + "\n")


if __name__ == "__main__":
    main()