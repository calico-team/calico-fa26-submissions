def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    K: the maximum number of seconds allowed for each query
    """
    BIG = 1 << 60
    tile = [[0 if ch == '.' else (1 if ch == 'R' else 2) for ch in row] for row in G]
    shortest = [BIG] * Q
    todo = [(0, M - 1, list(range(Q)))]
    while todo:
        left_col, right_col, ids = todo.pop()
        if not ids or left_col > right_col:
            continue
        w = right_col - left_col + 1
        center = (left_col + right_col) // 2
        area = N * w
        S = area * 2
        open_ = [False] * S
        plain = [False] * area
        for r in range(N):
            row = tile[r]
            base = r * w
            for c in range(w):
                t = row[left_col + c]
                i = base + c
                if t == 0:
                    plain[i] = True
                    open_[2 * i] = True
                    open_[2 * i + 1] = True
                elif t == 1:
                    open_[2 * i + 1] = True
                else:
                    open_[2 * i] = True
        colAt = [i % w for i in range(area)]
        maxc = w - 1
        fromPos = []
        toBlue = []
        toRed = []
        for q in ids:
            sr, sc = start[q]
            er, ec = end[q]
            fromPos.append((sr * w + sc - left_col) * 2)
            e = (er * w + ec - left_col) * 2
            toBlue.append(e)
            toRed.append(e + 1)
        step = 2 * w
        cc = center - left_col
        for r in range(N):
            for mode in range(2):
                origin = (r * w + cc) * 2 + mode
                if not open_[origin]:
                    continue
                far = [BIG] * S
                far[origin] = 0
                frontier = [origin]
                for x in frontier:
                    nxtd = far[x] + 1
                    cell = x >> 1
                    c = colAt[cell]
                    if c > 0:
                        y = x - 2
                        if open_[y] and far[y] == BIG:
                            far[y] = nxtd
                            frontier.append(y)
                    if c < maxc:
                        y = x + 2
                        if open_[y] and far[y] == BIG:
                            far[y] = nxtd
                            frontier.append(y)
                    y = x - step
                    if y >= 0 and open_[y] and far[y] == BIG:
                        far[y] = nxtd
                        frontier.append(y)
                    y = x + step
                    if y < S and open_[y] and far[y] == BIG:
                        far[y] = nxtd
                        frontier.append(y)
                    if plain[cell]:
                        y = x ^ 1
                        if far[y] == BIG:
                            far[y] = nxtd
                            frontier.append(y)
                for j in range(len(ids)):
                    a = far[fromPos[j]]
                    if a == BIG:
                        continue
                    b = far[toBlue[j]]
                    b2 = far[toRed[j]]
                    if b2 < b:
                        b = b2
                    if a + b < shortest[ids[j]]:
                        shortest[ids[j]] = a + b
        goL = []
        goR = []
        for q in ids:
            sc = start[q][1]
            ec = end[q][1]
            if sc < center and ec < center:
                goL.append(q)
            elif sc > center and ec > center:
                goR.append(q)
        todo.append((left_col, center - 1, goL))
        todo.append((center + 1, right_col, goR))
    return ["YES" if shortest[i] <= K[i] else "NO" for i in range(Q)]

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()