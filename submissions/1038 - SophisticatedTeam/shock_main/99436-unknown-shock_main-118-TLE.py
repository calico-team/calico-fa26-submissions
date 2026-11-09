import math
import sys


def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

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

            P2 = P * P
            P2_1 = P2 + 1

            # Iterate through vertical offsets dr from -P to P
            for dr in range(-P, P + 1):
                dr2 = dr * dr
                max_dc = math.isqrt(P2 - dr2)
                r_off = (R + dr) * M + C
                base_val = P2_1 - dr2

                # Center column (dc = 0)
                grid[r_off] = base_val

                # Symmetric horizontal offsets (dc > 0)
                for dc in range(1, max_dc + 1):
                    val = base_val - dc * dc
                    grid[r_off + dc] = val
                    grid[r_off - dc] = val

        # Stream output line-by-line to avoid memory overhead
        for r in range(N):
            row_slice = grid[r * M : (r + 1) * M]
            sys.stdout.write(" ".join(map(str, row_slice)) + "\n")


if __name__ == "__main__":
    solve()