import sys
 
 
def main():
    data = sys.stdin.read().split()
    p = 0
    T = int(data[p])
    p += 1
    out = []
    for _ in range(T):
        N = int(data[p])
        M = int(data[p + 1])
        Q = int(data[p + 2])
        p += 3
        G = data[p:p + N]
        p += N
        flat = ''.join(G)
        total = N * M
        ok = [None, None]
        ok[0] = [ch == '.' or ch == 'B' for ch in flat]
        ok[1] = [ch == '.' or ch == 'R' for ch in flat]
        comp = [-1] * (2 * total)
        cid = 0
        for start in range(2 * total):
            if comp[start] != -1:
                continue
            cell = start >> 1
            mode = start & 1
            if not ok[mode][cell]:
                continue
            comp[start] = cid
            stack = [start]
            while stack:
                s = stack.pop()
                cell = s >> 1
                mode = s & 1
                r, c = divmod(cell, M)
                good = ok[mode]
                if r > 0 and good[cell - M] and comp[s - 2 * M] == -1:
                    comp[s - 2 * M] = cid
                    stack.append(s - 2 * M)
                if r < N - 1 and good[cell + M] and comp[s + 2 * M] == -1:
                    comp[s + 2 * M] = cid
                    stack.append(s + 2 * M)
                if c > 0 and good[cell - 1] and comp[s - 2] == -1:
                    comp[s - 2] = cid
                    stack.append(s - 2)
                if c < M - 1 and good[cell + 1] and comp[s + 2] == -1:
                    comp[s + 2] = cid
                    stack.append(s + 2)
                if flat[cell] == '.':
                    t = s ^ 1
                    if comp[t] == -1:
                        comp[t] = cid
                        stack.append(t)
            cid += 1
        for _ in range(Q):
            r1 = int(data[p])
            c1 = int(data[p + 1])
            r2 = int(data[p + 2])
            c2 = int(data[p + 3])
            p += 4
            a = comp[(r1 * M + c1) * 2]
            e = r2 * M + c2
            if a != -1 and (comp[e * 2] == a or comp[e * 2 + 1] == a):
                out.append("YES")
            else:
                out.append("NO")
    print('\n'.join(out))
 
 
if __name__ == '__main__':
    main()
 