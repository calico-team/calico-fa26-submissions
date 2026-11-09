import sys
from math import isqrt


def final_readings(n, m, earthquakes):
    total = n * m
    readings = [0] * total

    # Each row has m cells and one sentinel. find() returns the first
    # unassigned cell at or after a given position in that row.
    stride = m + 1
    parent = list(range(n * stride))
    assigned = 0
    width_cache = {}

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    # Reverse time: the first earthquake covering a cell determines its answer.
    for center_r, center_c, power in reversed(earthquakes):
        widths = width_cache.get(power)
        if widths is None:
            widths = [
                isqrt(power * power - dr * dr)
                for dr in range(power + 1)
            ]
            width_cache[power] = widths

        power_squared = power * power
        for r in range(center_r - power, center_r + power + 1):
            dr = r - center_r
            width = widths[abs(dr)]
            base = r * stride
            left = center_c - width
            right_limit = base + center_c + width + 1
            position = find(base + left)
            row_base = r * m
            dr_squared = dr * dr

            while position < right_limit:
                c = position - base
                dc = c - center_c
                readings[row_base + c] = (
                    power_squared - dr_squared - dc * dc + 1
                )
                assigned += 1
                parent[position] = find(position + 1)
                position = find(position)

        if assigned == total:
            break

    return readings


def solve():
    input = sys.stdin.buffer.readline
    test_cases = int(input())
    output = []

    for _ in range(test_cases):
        n, m, q = map(int, input().split())
        earthquakes = [tuple(map(int, input().split())) for _ in range(q)]
        readings = final_readings(n, m, earthquakes)

        for r in range(n):
            start = r * m
            output.append(" ".join(map(str, readings[start:start + m])))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
