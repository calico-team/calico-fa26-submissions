import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    out = []
    for _ in range(T):
        N = int(next(iterator))
        K = int(next(iterator))

        groups_E = defaultdict(list)
        groups_N = defaultdict(list)

        for _ in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            _z = int(next(iterator))  
            d = next(iterator)

            s = x + y
            if d == "E":
                groups_E[s].append(x)
            else:
                groups_N[s].append(x)

        total_collisions = 0

        for s, e_xs in groups_E.items():
            if s in groups_N:
                n_xs = groups_N[s]
                n_xs.sort()

                for x_e in e_xs:
                    left = bisect_left(n_xs, x_e)
                    right = bisect_right(n_xs, x_e + K - 1)
                    total_collisions += right - left

        total_water = N * K - total_collisions
        out.append(str(total_water))

    print("\n".join(out))

if __name__ == "__main__":
    solve()