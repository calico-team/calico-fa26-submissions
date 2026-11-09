
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right


def solve():
    input = sys.stdin.readline
    test_cases = int(input())

    for _ in range(test_cases):
        drone_count, night_count = map(int, input().split())

        groups = defaultdict(list)

        for _ in range(drone_count):
            x, y, z, direction = input().split()
            x, y, z = int(x), int(y), int(z)

            groups[x + y].append((z, x, direction))

        blocked = 0

        for drones in groups.values():
            drones.sort(key=lambda drone: drone[0], reverse=True)

            coordinates = sorted({drone[1] for drone in drones})
            size = len(coordinates)

            east_tree = [0] * (size + 1)
            north_tree = [0] * (size + 1)

            def update(tree, index):
                index += 1
                while index <= size:
                    tree[index] += 1
                    index += index & -index

            def prefix_sum(tree, count):
                result = 0
                while count > 0:
                    result += tree[count]
                    count -= count & -count
                return result

            def range_count(tree, low, high):
                left = bisect_left(coordinates, low)
                right = bisect_right(coordinates, high)

                return (
                    prefix_sum(tree, right)
                    - prefix_sum(tree, left)
                )

            i = 0

            while i < len(drones):
                j = i

                while j < len(drones) and drones[j][0] == drones[i][0]:
                    j += 1

                # Count blockers with strictly greater height.
                for height, x, movement in drones[i:j]:
                    if movement == 'E':
                        blocked += range_count(
                            north_tree, x, x + night_count - 1
                        )
                    else:
                        blocked += range_count(
                            east_tree, x - night_count + 1, x
                        )

                # Add this height group only after querying it.
                for height, x, movement in drones[i:j]:
                    index = bisect_left(coordinates, x)

                    if movement == 'E':
                        update(east_tree, index)
                    else:
                        update(north_tree, index)

                i = j

        total_rain = drone_count * night_count - blocked
        print(total_rain)


if __name__ == "__main__":
    solve()
