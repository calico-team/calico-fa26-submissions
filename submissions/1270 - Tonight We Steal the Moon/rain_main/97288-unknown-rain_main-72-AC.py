import sys
from collections import defaultdict


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    idx = 0
    T = int(data[idx])
    idx += 1

    out = []
    for _ in range(T):
        N = int(data[idx])
        K = int(data[idx + 1])
        idx += 2

        diag_groups = defaultdict(list)

        for _ in range(N):
            X = int(data[idx])
            Y = int(data[idx + 1])
            Z = int(data[idx + 2])
            D = data[idx + 3]
            idx += 4
            diag_groups[X + Y].append((X, Z, D))

        total_water = N * K

        for S, drones in diag_groups.items():
            E_drones = []
            N_drones = []

            for X, Z, D in drones:
                if D == 'E':
                    E_drones.append(X)
                else:
                    N_drones.append(X)

            if not E_drones or not N_drones:
                continue

            E_drones.sort()
            N_drones.sort()

            left = 0
            right = 0
            n_N = len(N_drones)

            for X_E in E_drones:
                # Move 'left' pointer to the first North drone where X_N >= X_E
                while left < n_N and N_drones[left] < X_E:
                    left += 1
                while right < n_N and N_drones[right] < X_E + K:
                    right += 1

                total_water -= (right - left)

        out.append(str(total_water))

    print('\n'.join(out))


if __name__ == '__main__':
    solve()
