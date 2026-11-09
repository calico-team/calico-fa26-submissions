def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    comp = [[0] * M for _ in range(N)]
    cid = 0
    for i in range(N):
        for j in range(M):
            if comp[i][j] == 0:
                cid += 1
                comp[i][j] = cid
                st = [(i, j)]
                while st:
                    r, c = st.pop()
                    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < M and comp[nr][nc] == 0:
                            if (G[r][c] == 'R' and G[nr][nc] == 'B') or (G[r][c] == 'B' and G[nr][nc] == 'R'):
                                continue
                            comp[nr][nc] = cid
                            st.append((nr, nc))

    ans = []
    for i in range(Q):
        r1, c1 = start[i]
        r2, c2 = end[i]
        if comp[r1][c1] == comp[r2][c2]:
            ans.append("YES")
        else:
            ans.append("NO")
    return ans

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