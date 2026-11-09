import sys


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2]); pos += 3
        w = m + 2                       # grid padded with a blocked border -> no bounds checks
        size = (n + 2) * w              # states 0..size-1 = blue mode, size..2*size-1 = red mode

        # comp[state]: -2 = can't stand there in that mode, -1 = not labeled yet, >=0 = component id
        comp = [-2] * (2 * size)
        normal = bytearray(size)
        for r in range(n):
            row = data[pos + r]
            base = (r + 1) * w + 1
            for c in range(m):
                ch = row[c]
                if ch == 46:            # '.'  normal: active in both modes
                    comp[base + c] = -1
                    comp[size + base + c] = -1
                    normal[base + c] = 1
                elif ch == 66:          # 'B'  active only in blue mode
                    comp[base + c] = -1
                else:                   # 'R'  active only in red mode
                    comp[size + base + c] = -1
        pos += n

        steps = (1, -1, w, -w)
        cid = 0
        for s in range(2 * size):
            if comp[s] != -1:
                continue
            comp[s] = cid
            stack = [s]
            while stack:
                cur = stack.pop()
                if cur >= size:
                    idx = cur - size
                    other = idx
                else:
                    idx = cur
                    other = cur + size
                if normal[idx] and comp[other] == -1:      # spin (only on normal tiles)
                    comp[other] = cid
                    stack.append(other)
                for d in steps:                            # walk in the same mode
                    nxt = cur + d
                    if comp[nxt] == -1:
                        comp[nxt] = cid
                        stack.append(nxt)
            cid += 1

        for _ in range(q):
            sr = int(data[pos]); sc = int(data[pos + 1])
            er = int(data[pos + 2]); ec = int(data[pos + 3]); pos += 4
            start = comp[(sr + 1) * w + sc + 1]            # start tile is normal, so this is >= 0
            dest = (er + 1) * w + ec + 1
            if comp[dest] == start or comp[dest + size] == start:
                out.append("YES")
            else:
                out.append("NO")
    print("\n".join(out))


main()
