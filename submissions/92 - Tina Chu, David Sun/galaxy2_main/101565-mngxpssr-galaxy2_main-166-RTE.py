import numpy as np

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of whitilcol_endhar is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    scol_endonds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where eatilcol_endhar tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of eatilcol_endhar query
    end: the (row, column) of the ending tile of eatilcol_endhar query
    K: the maxValimum number of scol_endonds allowed for eatilcol_endhar query
    """
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
    SA = np.array([(col_start * N + sr) * 2 for sr, col_start in start], dtype = np.int64)
    # id of ending states for blue
    E0 = np.array([(col_end * N + er) * 2 for er, col_end in end], dtype = np.int64)

    col_start = np.array([col_start for i, col_start in start], dtype = np.int64)
    col_end = np.array([col_end for i, col_end in end], dtype = np.int64)

    # "best" meaning best time so far
    best = np.full(Q, maxVal, dtype = np.int64)

    stack = [(0, M-1, np.arange(Q))]

    while stack:
        leftCol, rightCol, queries = stack.pop()

        if len(queries) == 0:
            continue

        midCol = (leftCol + rightCol) // 2
        lo, hi = leftCol * statesPerCol, (rightCol + 1) * statesPerCol

        SAprime = SA[queries] - lo
        E0prime = E0[queries] - lo
        currentBest = best[queries]

        for searchState in range(midCol * statesPerCol, midCol * statesPerCol + statesPerCol):
            if not active[searchState]: continue

            distance = np.array(bfs(searchState, lo, hi), dtype = np.int64)

            # min over b/r version of end state
            time = distance[SAprime] + np.minimum(distance[E0prime], distance[E0prime + 1])
            np.minimum(currentBest, time, out=currentBest)

        best[queries] = currentBest

        queryStart = col_start[queries]
        queryEnd = col_end[queries]
        max = np.maximum(queryStart, queryEnd) # rightmost col of queries
        min = np.minimum(queryStart, queryEnd) # leftmost col of queries
        # "left is inferior/lesser"

        if leftCol < midCol:
            leftQueries_bounded = queries[max < midCol]
            if len(leftQueries_bounded):
                stack.append((leftCol, midCol - 1, leftQueries_bounded))

        if midCol < rightCol:
            rightQueries_bounded = queries[min > midCol]
            if len(rightQueries_bounded):
                stack.append((midCol + 1, rightCol, rightQueries_bounded))

    Ks = np.array(K, dtype = np.int64)

    for val in (best <= Ks):
        if val: result.append("YES")
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