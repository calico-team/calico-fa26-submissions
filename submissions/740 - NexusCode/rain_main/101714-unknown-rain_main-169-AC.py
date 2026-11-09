from bisect import bisect_left, bisect_right
from collections import defaultdict

def solve(N: int, K: int, X: list[int], Y: list[int], Z: list[int], D: list[str]) -> int:
    """
    Return the total amount of rainwater collected by all drones over all K nights.

    N: number of drones
    K: number of nights
    X: list of starting x-coordinates
    Y: list of starting y-coordinates
    Z: list of heights
    D: list of directions ('N' or 'E')
    """
    e_groups = defaultdict(list)
    n_groups = defaultdict(list)

    for i in range(N):
        s = X[i] + Y[i]
        if D[i] == 'E':
            e_groups[s].append(X[i])
        else:
            n_groups[s].append(X[i])

    total_blocked = 0

    for s, n_list in n_groups.items():
        if s not in e_groups:
            continue

        e_list = e_groups[s]
        e_list.sort()

        for x_n in n_list:
            low = x_n - K + 1
            high = x_n
            left_idx = bisect_left(e_list, low)
            right_idx = bisect_right(e_list, high)
            total_blocked += (right_idx - left_idx)

    return N * K - total_blocked

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        X = []
        Y = []
        Z = []
        D = []
        for _ in range(N):
            line = input().split()
            X.append(int(line[0]))
            Y.append(int(line[1]))
            Z.append(int(line[2]))
            D.append(line[3])
        print(solve(N, K, X, Y, Z, D))

if __name__ == '__main__':
    main()