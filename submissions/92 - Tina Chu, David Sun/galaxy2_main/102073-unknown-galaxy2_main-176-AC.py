def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    '''
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i], and "NO"
    otherwise.
    
    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the {row, column} of the starting tile of each query
    end: the {row, column} of the ending tile of each query
    '''
    # YOUR CODE HERE
    result = []

    statesPerCol = 2*N
    statesPerTot = statesPerCol*M
    maxVal = 10**18

    active = [False] * statesPerTot
    normal = [False] * statesPerTot
    rowOf_stateI = [0] * statesPerTot

    for column in range(M):
        for row in range(N):
            base = ((column*N) + row)*2
            tileChar = G[row][column]
            rowOf_stateI[base], rowOf_stateI[base+1] = row, row

            if tileChar == '.':
                active[base], active[base+1] = True, True
                normal[base], normal[base+1] = True, True

            elif tileChar == 'B':
                active[base] = True

            else:
                active[base+1] = True

    def bfs(searchState, lowID, highID):
        distance = [maxVal]*(highID - lowID)
        distance[searchState - lowID] = 0
        bounds = [searchState]
        time = 0

        while bounds:
            time += 1
            next = []

            # g: state being expanded now
            # h: neighboring state
            for g in bounds:
                # spin action
                if normal[g]:
                    h = g ^ 1
                    if distance[h - lowID] == maxVal:
                        distance[h - lowID] = time
                        next.append(h)

                # left action
                h = g - statesPerCol
                if h >= lowID and active[h] and distance[h - lowID] == maxVal:
                    distance[h - lowID] = time
                    next.append(h)

                # right action
                h = g + statesPerCol
                if h < highID and active[h] and distance[h - lowID] == maxVal:
                    distance[h - lowID] = time
                    next.append(h)

                # up action
                if rowOf_stateI[g] > 0:
                    h = g - 2
                    if active[h] and distance[h - lowID] == maxVal:
                        distance[h - lowID] = time
                        next.append(h)

                # down action
                if rowOf_stateI[g] < N - 1:
                    h = g + 2
                    if active[h] and distance[h - lowID] == maxVal:
                        distance[h - lowID] = time
                        next.append(h)

            bounds = next
        return distance

    # id of starting states of each query
    SA = [(sc * N + sr) * 2 for sr, sc in start]
    # id of ending states for blue
    E0 = [(ec * N + er) * 2 for er, ec in end]

    col_start = [sc for sr, sc in start]
    col_end = [ec for er, ec in end]

    # "best" meaning best time so far
    best = [maxVal] * Q

    stack = [(0, M-1, list(range(Q)))]

    while stack:
        leftCol, rightCol, queries = stack.pop()

        if not queries:
            continue

        midCol = (leftCol + rightCol) // 2
        lo, hi = leftCol * statesPerCol, (rightCol + 1) * statesPerCol

        SAprime = [SA[i] - lo for i in queries]
        E0prime = [E0[i] - lo for i in queries]
        currentBest = [best[i] for i in queries]

        for searchState in range(midCol * statesPerCol, midCol * statesPerCol + statesPerCol):
            if not active[searchState]: continue

            distance = bfs(searchState, lo, hi)

            for j in range(len(queries)):
                e = E0prime[j]
                endDist = distance[e]
                redDist = distance[e + 1]

                # min over b/r version of end state
                if redDist < endDist:
                    endDist = redDist
                time = distance[SAprime[j]] + endDist
                if time < currentBest[j]:
                    currentBest[j] = time

        for j in range(len(queries)):
            best[queries[j]] = currentBest[j]

        leftQueries_bounded = []
        rightQueries_bounded = []
        for i in queries:
            a = col_start[i]
            b = col_end[i]
            if a > b:
                a, b = b, a
            # a = leftmost col of query, b = rightmost col of query
            # "left is inferior/lesser"

            if b < midCol:
                leftQueries_bounded.append(i)
            elif a > midCol:
                rightQueries_bounded.append(i)

        if leftCol < midCol and leftQueries_bounded:
            stack.append((leftCol, midCol - 1, leftQueries_bounded))

        if midCol < rightCol and rightQueries_bounded:
            stack.append((midCol + 1, rightCol, rightQueries_bounded))

    for i in range(Q):
        if best[i] <= K[i]: result.append("YES")
        else: result.append("NO")

    return result

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