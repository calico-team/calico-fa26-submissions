import sys
from math import isqrt


def final_readings(n, m, earthquakes):
    total = n * m
    readings = [0] * total

    # Bit c of unassigned[r] is 1 exactly when row r, column c still needs
    # its final value. Reverse time makes each cell change at most once.
    full_row = (1 << m) - 1
    unassigned = [full_row] * n
    assigned = 0

    width_cache = {}
    interval_cache = {}
    circle_cache = {}
    seen_circles = set()
    modulus = m + 1
    cached_circle_bits = 0

    for center_r, center_c, power in reversed(earthquakes):
        circle_key = (center_c, power)
        circle_masks = circle_cache.get(circle_key)
        widths = None

        if circle_masks is None:
            widths = width_cache.get(power)
            if widths is None:
                p2 = power * power
                widths = [isqrt(p2 - dr * dr) for dr in range(power + 1)]
                width_cache[power] = widths

            # Cache the whole circle when it occurs again. This makes heavily
            # overlapping earthquakes cheap without unbounded cache growth.
            estimated_bits = (power + 1) * m
            if (circle_key in seen_circles and
                    cached_circle_bits + estimated_bits <= 100_000_000):
                circle_masks = [None] * (power + 1)
                for dr in range(power + 1):
                    width = widths[dr]
                    left = center_c - width
                    key = left * modulus + width
                    interval = interval_cache.get(key)
                    if interval is None:
                        interval = ((1 << (2 * width + 1)) - 1) << left
                        if len(interval_cache) < 200_000:
                            interval_cache[key] = interval
                    circle_masks[dr] = interval
                circle_cache[circle_key] = circle_masks
                cached_circle_bits += estimated_bits
            else:
                seen_circles.add(circle_key)

        p2 = power * power
        for dr in range(power + 1):
            if circle_masks is not None:
                interval = circle_masks[dr]
            else:
                width = widths[dr]
                left = center_c - width
                key = left * modulus + width
                interval = interval_cache.get(key)
                if interval is None:
                    interval = ((1 << (2 * width + 1)) - 1) << left
                    if len(interval_cache) < 200_000:
                        interval_cache[key] = interval

            base_value = p2 - dr * dr + 1
            rows = ((center_r,) if dr == 0
                    else (center_r - dr, center_r + dr))

            for r in rows:
                targets = unassigned[r] & interval
                if not targets:
                    continue

                unassigned[r] ^= targets
                assigned += targets.bit_count()
                row_base = r * m

                while targets:
                    lowest_bit = targets & -targets
                    c = lowest_bit.bit_length() - 1
                    dc = c - center_c
                    readings[row_base + c] = base_value - dc * dc
                    targets ^= lowest_bit

        if assigned == total:
            break

    return readings


def solve():
    input = sys.stdin.buffer.readline
    test_cases = int(input())
    write = sys.stdout.write

    for case in range(test_cases):
        n, m, q = map(int, input().split())
        earthquakes = [tuple(map(int, input().split())) for _ in range(q)]
        readings = final_readings(n, m, earthquakes)

        if case:
            write("\n")
        write("\n".join(
            " ".join(map(str, readings[r * m:(r + 1) * m]))
            for r in range(n)
        ))


if __name__ == "__main__":
    solve()
