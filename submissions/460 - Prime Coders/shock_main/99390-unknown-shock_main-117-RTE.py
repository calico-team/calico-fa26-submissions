
from math import isqrt
from array import array


def solve(N, M, Q, earthquakes):

    # Initially, every block has reading 0.
    answer = [[0] * M for _ in range(N)]

    # DSU: each row has its own next-unassigned-column structure.
    # The extra column is a sentinel.
    width = M + 1
    parent = array('i', range(N * width))

    def find(x):
        # Find the next column that has not been assigned.
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]

        return x

    # Process earthquakes in reverse order.
    for X, Y, P in reversed(earthquakes):

        power_squared = P * P

        # Visit only rows inside the earthquake's radius.
        for row in range(Y - P, Y + P + 1):

            dy = row - Y

            # Calculate the horizontal radius for this row.
            remaining = power_squared - dy * dy
            dx = isqrt(remaining)

            left = X - dx
            right = X + dx

            # Start from the first unassigned column.
            row_start = row * width
            col = find(row_start + left)

            while col <= row_start + right:

                current_col = col - row_start

                distance_squared = (
                    dy * dy +
                    (current_col - X) * (current_col - X)
                )

                shock = power_squared - distance_squared + 1

                answer[row][current_col] = shock

                # Remove this column from future consideration.
                parent[col] = find(col + 1)

                # Find the next unassigned column.
                col = find(col)

    return answer


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        earthquakes = []

        for _ in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))

        answer = solve(N, M, Q, earthquakes)

        for row in answer:
            print(' '.join(map(str, row)))


if __name__ == '__main__':
    main()
