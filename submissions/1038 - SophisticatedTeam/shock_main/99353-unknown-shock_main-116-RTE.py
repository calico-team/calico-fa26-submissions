import math
import sys


def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    out = []
    patterns = {}

    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))

        # Flattened 1D city grid initialized to 0
        grid = [0] * (N * M)

        for _ in range(Q):
            R = int(next(iterator))
            C = int(next(iterator))
            P = int(next(iterator))

            # Fetch or build offset pattern for (P, M)
            key = (P, M)
            if key in patterns:
                pat = patterns[key]
            else:
                pat = []
                P2_1 = P * P + 1
                for dr in range(-P, P + 1):
                    dr2 = dr * dr
                    max_dc = math.isqrt(P * P - dr2)
                    r_off = dr * M
                    for dc in range(-max_dc, max_dc + 1):
                        val = P2_1 - dr2 - dc * dc
                        pat.append((r_off + dc, val))
                patterns[key] = pat

            # Apply shock updates directly to 1D grid
            center = R * M + C
            for off, val in pat:
                grid[center + off] = val

        # Fast string formatting per row slice
        for r in range(N):
            out.append(" ".join(map(str, grid[r * M : (r + 1) * M])))

    print("\n".join(out))


if __name__ == "__main__":
    solve()