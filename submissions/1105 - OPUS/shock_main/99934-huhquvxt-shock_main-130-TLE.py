import sys
from math import isqrt

input = sys.stdin.readline

def solve():
    T = int(input())

    for _ in range(T):
        rows, cols, q = map(int, input().split())
        events = [tuple(map(int, input().split())) for _ in range(q)]

        grid = [[0] * cols for _ in range(rows)]
        pending = [(1 << cols) - 1 for _ in range(rows)]

        remaining = rows * cols

        for cy, cx, power in reversed(events):
            radius2 = power * power

            for y in range(cy - power, cy + power + 1):
                dy = y - cy
                dx = isqrt(radius2 - dy * dy)

                left = cx - dx
                right = cx + dx

                mask = ((1 << (right - left + 1)) - 1) << left
                fresh = pending[y] & mask

                if fresh == 0:
                    continue

                pending[y] ^= fresh
                remaining -= fresh.bit_count()

                while fresh:
                    bit = fresh & -fresh
                    x = bit.bit_length() - 1

                    distance2 = dy * dy + (x - cx) ** 2
                    grid[y][x] = radius2 - distance2 + 1

                    fresh ^= bit

            if remaining == 0:
                break

        for line in grid:
            print(*line)


solve()
