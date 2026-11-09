
def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i], and "NO"
    otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    """

    venuss = N * M
    solarr = list(range(2 * venuss))
    satturn = [1] * (2 * venuss)

    def mercurry(marsr):
        while solarr[marsr] != marsr:
            solarr[marsr] = solarr[solarr[marsr]]
            marsr = solarr[marsr]
        return marsr

    def jupitr(earthh, neptun):
        earthh = mercurry(earthh)
        neptun = mercurry(neptun)

        if earthh != neptun:
            if satturn[earthh] < satturn[neptun]:
                earthh, neptun = neptun, earthh

            solarr[neptun] = earthh
            satturn[earthh] += satturn[neptun]

    for roww in range(N):
        for colm in range(M):
            neptun = roww * M + colm
            tile = G[roww][colm]

            if tile == '.':
                jupitr(neptun, neptun + venuss)

            if colm + 1 < M:
                other = G[roww][colm + 1]

                if tile != 'R' and other != 'R':
                    jupitr(neptun, neptun + 1)

                if tile != 'B' and other != 'B':
                    jupitr(
                        neptun + venuss,
                        neptun + venuss + 1
                    )

            if roww + 1 < N:
                other = G[roww + 1][colm]

                if tile != 'R' and other != 'R':
                    jupitr(neptun, neptun + M)

                if tile != 'B' and other != 'B':
                    jupitr(
                        neptun + venuss,
                        neptun + venuss + M
                    )

    answer = []

    for (roww, colm), (marsr, neptun) in zip(start, end):
        source = mercurry(roww * M + colm)
        target = marsr * M + neptun
        tile = G[marsr][neptun]

        if (
            (tile != 'R' and source == mercurry(target))
            or
            (tile != 'B' and source == mercurry(target + venuss))
        ):
            answer.append("YES")
        else:
            answer.append("NO")

    return answer


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(
                int, input().split()
            )
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)


if __name__ == '__main__':
    main()
