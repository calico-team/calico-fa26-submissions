import sys

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []
    for _ in range(t):
        n = int(data[p]); m = int(data[p+1]); q = int(data[p+2]); p += 3
        W = m + 2
        size = (n + 2) * W
        act0 = bytearray(size)   # active in blue mode
        act1 = bytearray(size)   # active in red mode
        normal = bytearray(size)
        for r in range(n):
            row = data[p + r]
            base = (r + 1) * W + 1
            for c in range(m):
                ch = row[c]
                if ch == 46:        # '.'
                    act0[base + c] = 1; act1[base + c] = 1; normal[base + c] = 1
                elif ch == 66:      # 'B'
                    act0[base + c] = 1
                else:               # 'R'
                    act1[base + c] = 1
        p += n
        acts = (act0, act1)
        compid = [[0] * size, [0] * size]
        cid = 0
        dirs = (1, -1, W, -W)
        for mode in (0, 1):
            act = acts[mode]
            cm = compid[mode]
            for s in range(size):
                if act[s] and cm[s] == 0:
                    cid += 1
                    cm[s] = cid
                    stack = [(s, mode)]
                    while stack:
                        x, md = stack.pop()
                        a = acts[md]
                        cmd = compid[md]
                        for d in dirs:
                            y = x + d
                            if a[y] and cmd[y] == 0:
                                cmd[y] = cid
                                stack.append((y, md))
                        if normal[x]:
                            o = 1 - md
                            co = compid[o]
                            if co[x] == 0:
                                co[x] = cid
                                stack.append((x, o))
        for _q in range(q):
            rs = int(data[p]); cs = int(data[p+1]); re = int(data[p+2]); ce = int(data[p+3]); p += 4
            s = (rs + 1) * W + cs + 1
            e = (re + 1) * W + ce + 1
            k = compid[0][s]
            if k != 0 and (compid[0][e] == k or compid[1][e] == k):
                out.append("YES")
            else:
                out.append("NO")
    sys.stdout.write("\n".join(out) + "\n")

main()