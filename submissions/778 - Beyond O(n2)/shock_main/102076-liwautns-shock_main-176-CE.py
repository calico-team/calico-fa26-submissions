import re
import sys
from math import isqrt

nonzero = re.compile(rb"[\x01-\xff]")
data = list(map(int, sys.stdin.buffer.read().split()))
pos = 0

t = data[pos]
pos += 1

answers = []
shape_cache = {}

for _ in range(t):
    n = data[pos]
    m = data[pos + 1]
    q = data[pos + 2]
    pos += 3

    quakes = []
    max_p = 0

    for _ in range(q):
        r = data[pos]
        c = data[pos + 1]
        p = data[pos + 2]
        pos += 3
        quakes.append((r, c, p))
        max_p = max(max_p, p)

    transpose = n < m and max_p > 3

    if transpose:
        h, w = m, n
    else:
        h, w = n, m

    grid = [[0] * w for _ in range(h)]

    if max_p <= 3:
        cell_cache = {}

        for r, c, p in reversed(quakes):
            if p not in cell_cache:
                cells = []
                p2 = p * p

                for dr in range(-p, p + 1):
                    dc_max = isqrt(p2 - dr * dr)
                    for dc in range(-dc_max, dc_max + 1):
                        cells.append((dr, dc))

                cell_cache[p] = cells

            p2 = p * p
            for dr, dc in cell_cache[p]:
                row = r + dr
                col = c + dc

                if grid[row][col] == 0:
                    grid[row][col] = p2 - dr * dr - dc * dc + 1

    elif h <= 2000:
        stride = (w + 7) // 8 * 8
        unassigned = (1 << (h * stride)) - 1

        for r, c, p in reversed(quakes):
            if transpose:
                r, c = c, r

            if p == 0:
                if grid[r][c] == 0:
                    grid[r][c] = 1
                continue

            key = (p, w, stride)

            if key not in shape_cache:
                size = 2 * p + 1
                row_bytes = stride // 8
                mask_bytes = bytearray(size * row_bytes)
                p2 = p * p

                for dr in range(-p, p + 1):
                    dc = isqrt(p2 - dr * dr)
                    left = p - dc
                    right = p + dc

                    start_byte = (dr + p) * row_bytes + left // 8
                    end_byte = (dr + p) * row_bytes + right // 8
                    start_bit = left % 8
                    end_bit = right % 8

                    if start_byte == end_byte:
                        mask_bytes[start_byte] |= (
                            ((1 << (end_bit - start_bit + 1)) - 1)
                            << start_bit
                        )
                    else:
                        mask_bytes[start_byte] |= (255 << start_bit) & 255

                        if end_byte > start_byte + 1:
                            mask_bytes[start_byte + 1:end_byte] = (
                                b"\xff" * (end_byte - start_byte - 1)
                            )

                        mask_bytes[end_byte] |= (1 << (end_bit + 1)) - 1

                shape_cache[key] = int.from_bytes(mask_bytes, "little")

            offset = (r - p) * stride + (c - p)
            mask = shape_cache[key] << offset
            bits = unassigned & mask

            if bits:
                unassigned ^= bits
                raw = bits.to_bytes((bits.bit_length() + 7) // 8, "little")
                p2 = p * p

                for match in nonzero.finditer(raw):
                    byte_pos = match.start()
                    byte = raw[byte_pos]

                    while byte:
                        low_bit = byte & -byte
                        index = byte_pos * 8 + low_bit.bit_length() - 1
                        row, col = divmod(index, stride)

                        if grid[row][col] == 0:
                            dr = row - r
                            dc = col - c
                            grid[row][col] = p2 - dr * dr - dc * dc + 1

                        byte -= low_bit

    else:
        unassigned = [(1 << w) - 1] * h
        rows_cache = {}

        for r, c, p in reversed(quakes):
            if transpose:
                r, c = c, r

            if p == 0:
                if grid[r][c] == 0:
                    grid[r][c] = 1
                continue

            if p not in rows_cache:
                offsets = []
                p2 = p * p

                for dr in range(-p, p + 1):
                    dc = isqrt(p2 - dr * dr)
                    offsets.append((dr, dc, (1 << (2 * dc + 1)) - 1)

                rows_cache[p] = offsets

            p2 = p * p

            for dr, dc, base_mask in rows_cache[p]:
                row = r + dr
                left = c - dc
                mask = base_mask << left
                bits = unassigned[row] & mask

                if bits:
                    unassigned[row] &= ~mask

                    while bits:
                        low_bit = bits & -bits
                        col = low_bit.bit_length() - 1

                        if grid[row][col] == 0:
                            diff = col - c
                            grid[row][col] = (
                                p2 - dr * dr - diff * diff + 1
                            )

                        bits -= low_bit

    if transpose:
        for r in range(n):
            answers.append(
                " ".join(str(grid[c][r]) for c in range(m))
            )
    else:
        for row in grid:
            answers.append(" ".join(map(str, row)))

sys.stdout.write("\n".join(answers) + "\n")