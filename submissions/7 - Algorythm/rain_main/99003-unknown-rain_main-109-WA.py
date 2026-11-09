
"""
* Return an integer denoting the amount of rain collected after the Kth nights
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""

from collections import defaultdict
from bisect import bisect_left, bisect_right


def solve(N: int, K: int, L: list):

    diagonal_groups = defaultdict(list)

    for drone_x, drone_y, drone_z, drone_dir in L:
        diagonal_groups[drone_x + drone_y].append(
            (drone_z, drone_x, drone_dir)
        )

    blocked_nights = 0

    for drone_group in diagonal_groups.values():

        x_positions = sorted(item[1] for item in drone_group)
        group_size = len(x_positions)

        east_tree = [0] * (group_size + 1)
        north_tree = [0] * (group_size + 1)

        def get_sum(tree, position):
            result = 0

            while position > 0:
                result += tree[position]
                position -= position & -position

            return result

        def add_value(tree, position):
            while position <= group_size:
                tree[position] += 1
                position += position & -position

        drone_group.sort(reverse=True)

        index = 0

        while index < len(drone_group):

            current_height = drone_group[index][0]
            next_index = index

            while (next_index < len(drone_group) and
                   drone_group[next_index][0] == current_height):

                next_index += 1

            # Query before inserting drones of equal height.
            for drone_z, drone_x, drone_dir in drone_group[index:next_index]:

                left_bound = drone_x
                right_bound = drone_x + K - 1

                left_index = bisect_left(x_positions, left_bound)
                right_index = bisect_right(x_positions, right_bound)

                if drone_dir == 'E':
                    opposite_tree = north_tree
                else:
                    opposite_tree = east_tree

                blocked_nights += (
                    get_sum(opposite_tree, right_index)
                    - get_sum(opposite_tree, left_index)
                )

            # Insert current-height drones after all queries.
            for drone_z, drone_x, drone_dir in drone_group[index:next_index]:

                position = bisect_left(x_positions, drone_x) + 1

                if drone_dir == 'E':
                    add_value(east_tree, position)
                else:
                    add_value(north_tree, position)

            index = next_index

    return N * K - blocked_nights


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        L = []

        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))


if __name__ == '__main__':
    main()
