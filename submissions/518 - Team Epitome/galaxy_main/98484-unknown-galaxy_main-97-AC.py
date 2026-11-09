from collections import deque

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:

    def isActive(r, c, mode):
        ch = G[r][c]
        if ch == '.':
            return True
        if ch == 'B':
            return mode == 0
        return mode == 1

    comp = [-1] * (N * M * 2)
    count = 0
    for r in range(N):
        for c in range(M):
            for mode in range(2):
                idx = (r * M + c) * 2 + mode
                if comp[idx] != -1 or not isActive(r, c, mode):
                    continue
                comp[idx] = count
                dq = deque([(r, c, mode)])
                while dq:
                    cr, cc, cm = dq.popleft()
                    if G[cr][cc] == '.':
                        nm = 1 - cm
                        ni = (cr * M + cc) * 2 + nm
                        if comp[ni] == -1:
                            comp[ni] = count
                            dq.append((cr, cc, nm))
                    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        nr, nc = cr + dr, cc + dc
                        if 0 <= nr < N and 0 <= nc < M and isActive(nr, nc, cm):
                            ni = (nr * M + nc) * 2 + cm
                            if comp[ni] == -1:
                                comp[ni] = count
                                dq.append((nr, nc, cm))
                count += 1

    result = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        s = comp[(sr * M + sc) * 2]
        ok = False
        for mode in range(2):
            if isActive(er, ec, mode) and comp[(er * M + ec) * 2 + mode] == s:
                ok = True
                break
        result.append("YES" if ok else "NO")
    return result


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)


if __name__ == '__main__':
    main()