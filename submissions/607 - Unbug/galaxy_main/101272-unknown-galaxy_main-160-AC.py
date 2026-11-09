import sys

def solve(N, M, Q, G, start, end):
    comp = [[-1, -1] for _ in range(N * M)]
    cid = 0

    for r in range(N):
        rM = r * M
        for c in range(M):
            cell = rM + c
            tile = G[r][c]
            for m in (0, 1):
                allowed = ('.', 'B') if m == 0 else ('.', 'R')
                if tile in allowed and comp[cell][m] == -1:
                    comp[cell][m] = cid
                    q = [(r, c, m)]
                    
                    for cr, cc, cm in q:
                        ccell = cr * M + cc
                        if G[cr][cc] == '.' and comp[ccell][1 - cm] == -1:
                            comp[ccell][1 - cm] = cid
                            q.append((cr, cc, 1 - cm))
                        
                        cur_allowed = ('.', 'B') if cm == 0 else ('.', 'R')
                        if cr > 0 and G[cr - 1][cc] in cur_allowed and comp[ccell - M][cm] == -1:
                            comp[ccell - M][cm] = cid
                            q.append((cr - 1, cc, cm))
                        if cr + 1 < N and G[cr + 1][cc] in cur_allowed and comp[ccell + M][cm] == -1:
                            comp[ccell + M][cm] = cid
                            q.append((cr + 1, cc, cm))
                        if cc > 0 and G[cr][cc - 1] in cur_allowed and comp[ccell - 1][cm] == -1:
                            comp[ccell - 1][cm] = cid
                            q.append((cr, cc - 1, cm))
                        if cc + 1 < M and G[cr][cc + 1] in cur_allowed and comp[ccell + 1][cm] == -1:
                            comp[ccell + 1][cm] = cid
                            q.append((cr, cc + 1, cm))
                    cid += 1

    ans = []
    for (sr, sc), (er, ec) in zip(start, end):
        scid = comp[sr * M + sc][0]
        ecell = er * M + ec
        if comp[ecell][0] == scid or comp[ecell][1] == scid:
            ans.append('YES')
        else:
            ans.append('NO')

    return ans


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))
    out = []
    
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        G = [next(iterator) for _ in range(N)]
        start, end = [], []
        for _ in range(Q):
            sr = int(next(iterator))
            sc = int(next(iterator))
            er = int(next(iterator))
            ec = int(next(iterator))
            start.append((sr, sc))
            end.append((er, ec))
        out.extend(solve(N, M, Q, G, start, end))

    print('\n'.join(out))


if __name__ == '__main__':
    main()