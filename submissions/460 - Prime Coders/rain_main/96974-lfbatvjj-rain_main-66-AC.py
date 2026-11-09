
from bisect import bisect_left, bisect_right


def solve(N: int, K: int, L: list) -> int:
    """
    Return the total amount of rain collected
    after K nights.
    """

    groups = {}

    # Group drones according to X + Y
    for X, Y, Z, D in L:

        key = X + Y

        if key not in groups:
            groups[key] = {"E": [], "N": []}

        groups[key][D].append(X)

    # Count total collisions
    collisions = 0

    for group in groups.values():

        east = group["E"]
        north = sorted(group["N"])

        # Count possible meetings
        for x in east:

            left = bisect_left(north, x)
            right = bisect_right(north, x + K - 1)

            collisions += right - left

    # Initially, every drone collects 1 unit each night
    total = N * K

    # Each collision causes one drone to lose 1 unit
    return total - collisions


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
