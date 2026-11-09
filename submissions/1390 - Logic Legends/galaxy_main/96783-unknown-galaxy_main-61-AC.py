def solve(N, M, Q, G, start, end):
    flat = ''.join(G)
    total = N * M
    ok = [[ch == '.' or ch == 'B' for ch in flat], [ch == '.' or ch == 'R' for ch in flat]]
    comp = [-1] * (2 * total)
    cid = 0
    for st in range(2 * total):
        if comp[st] != -1:
            continue
        if not ok[st & 1][st >> 1]:
            continue
        comp[st] = cid
        stack = [st]
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
            if flat[cell] == '.' and comp[s ^ 1] == -1:
                comp[s ^ 1] = cid
                stack.append(s ^ 1)
        cid += 1
    res = []
    for i in range(Q):
        a = comp[(start[i][0] * M + start[i][1]) * 2]
        e = end[i][0] * M + end[i][1]
        if a != -1 and (comp[e * 2] == a or comp[e * 2 + 1] == a):
            res.append("YES")
        else:
            res.append("NO")
    return res
 
 
def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input().strip())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)
 
 
if __name__ == '__main__':
    main()
 