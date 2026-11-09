import sys


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    bad = {(82, 66), (66, 82)}
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2]); pos += 3
        g = b''.join(data[pos:pos + n]); pos += n
        nm = n * m
        comp = [-1] * nm
        c = 0
        for s in range(nm):
            if comp[s] >= 0:
                continue
            comp[s] = c
            stack = [s]
            while stack:
                u = stack.pop()
                cu = g[u]
                r, col = divmod(u, m)
                if col > 0:
                    v = u - 1
                    if comp[v] < 0 and (cu, g[v]) not in bad:
                        comp[v] = c; stack.append(v)
                if col < m - 1:
                    v = u + 1
                    if comp[v] < 0 and (cu, g[v]) not in bad:
                        comp[v] = c; stack.append(v)
                if r > 0:
                    v = u - m
                    if comp[v] < 0 and (cu, g[v]) not in bad:
                        comp[v] = c; stack.append(v)
                if r < n - 1:
                    v = u + m
                    if comp[v] < 0 and (cu, g[v]) not in bad:
                        comp[v] = c; stack.append(v)
            c += 1
        for i in range(pos, pos + 4 * q, 4):
            a = int(data[i]) * m + int(data[i + 1])
            b = int(data[i + 2]) * m + int(data[i + 3])
            out.append("YES" if comp[a] == comp[b] else "NO")
        pos += 4 * q
    sys.stdout.write("\n".join(out) + "\n")


main()
