import sys
input = sys.stdin.readline


def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    grup = [[-1] * M for _ in range(N)]
    say = 0
    for i in range(N):
        for j in range(M):
            if grup[i][j] != -1:
                continue
            grup[i][j] = say
            yigin = [(i, j)]
            while yigin:
                x, y = yigin.pop()
                for a, b in ((x+1, y), (x-1, y), (x, y+1), (x, y-1)):
                    if 0 <= a < N and 0 <= b < M and grup[a][b] == -1:
                        # R ile B yan yana gecilemez
                        if G[x][y] + G[a][b] in ("RB", "BR"):
                            continue
                        grup[a][b] = say
                        yigin.append((a, b))
            say += 1

    cevap = []
    for (r1, c1), (r2, c2) in zip(start, end):
        cevap.append("YES" if grup[r1][c1] == grup[r2][c2] else "NO")
    return cevap


def main():
    T = int(input())
    out = []
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
        out.extend(solve(N, M, Q, G, start, end))
    print("\n".join(out))


if __name__ == '__main__':
    main()