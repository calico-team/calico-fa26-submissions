import sys
from bisect import bisect_left


def calculate_total(n, k, groups):
    blocked = 0

    for east, north in groups.values():
        if not east or not north:
            continue

        east.sort()
        north.sort()

        # A pair meets when s = x_e + y_e = x_n + y_n and
        # 0 <= x_n - x_e < K. Count all such pairs in this group.
        for x in east:
            left = bisect_left(north, x)
            right = bisect_left(north, x + k)
            blocked += right - left

    # Every meeting blocks exactly one drone for exactly one night.
    return n * k - blocked


def solve():
    input = sys.stdin.buffer.readline
    test_cases = int(input())
    answers = []

    for _ in range(test_cases):
        n, k = map(int, input().split())
        groups = {}

        for _ in range(n):
            x_raw, y_raw, _, direction = input().split()
            x = int(x_raw)
            y = int(y_raw)
            coordinate_sum = x + y

            if coordinate_sum not in groups:
                groups[coordinate_sum] = ([], [])

            if direction == b"E":
                groups[coordinate_sum][0].append(x)
            else:
                groups[coordinate_sum][1].append(x)

        answers.append(str(calculate_total(n, k, groups)))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
