import sys
from bisect import bisect_left, bisect_right


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    it = iter(data)
    t = int(next(it))
    answers = []

    for _ in range(t):
        n = int(next(it))
        k = int(next(it))
        groups = {}

        for _ in range(n):
            x = int(next(it))
            y = int(next(it))
            z = int(next(it))
            direction = next(it).decode()

            diagonal = x + y
            if diagonal not in groups:
                groups[diagonal] = [[], []]

            if direction == "E":
                groups[diagonal][0].append(x)
            else:
                groups[diagonal][1].append(x)

        blocked_nights = 0

        for east_x, north_x in groups.values():
            east_x.sort()
            for x_n in north_x:
                left = bisect_left(east_x, x_n - k + 1)
                right = bisect_right(east_x, x_n)
                blocked_nights += right - left

        total_rain = n * k - blocked_nights
        answers.append(str(total_rain))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
