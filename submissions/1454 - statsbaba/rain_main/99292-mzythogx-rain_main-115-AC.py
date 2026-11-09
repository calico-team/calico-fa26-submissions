import sys
from bisect import bisect_left
from collections import defaultdict


def solve():
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return

    position = 0
    test_count = int(tokens[position])
    position += 1
    answers = []

    for _ in range(test_count):
        drone_count = int(tokens[position])
        night_count = int(tokens[position + 1])
        position += 2

        east_by_diagonal = defaultdict(list)
        north_by_diagonal = defaultdict(list)

        for _ in range(drone_count):
            x = int(tokens[position])
            y = int(tokens[position + 1])
            z = int(tokens[position + 2])
            direction = tokens[position + 3]
            position += 4

            diagonal = x + y

            if direction == b'E':
                east_by_diagonal[diagonal].append(x)
            else:
                north_by_diagonal[diagonal].append(x)

        collision_count = 0

        for diagonal, east_x_values in east_by_diagonal.items():
            north_x_values = north_by_diagonal.get(diagonal)
            if not north_x_values:
                continue

            north_x_values.sort()

            for east_x in east_x_values:
                left_index = bisect_left(north_x_values, east_x)
                right_index = bisect_left(north_x_values, east_x + night_count)
                collision_count += right_index - left_index

        total_rain = drone_count * night_count - collision_count
        answers.append(str(total_rain))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()