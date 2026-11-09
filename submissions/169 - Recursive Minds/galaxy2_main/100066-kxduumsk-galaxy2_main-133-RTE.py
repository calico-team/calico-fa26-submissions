from collections import deque
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
    results = []
    layerkasize = N * M
    visited_id = [-1] * (2 * layerkasize)
    dist = [0] * (2 * layerkasize)
    
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        KK = K[i]
        
        if abs(rs - re) + abs(cs - ce) > K:
            results.append("NO")
            continue
        
        startidx = rs * M + ce
        startnode = startidx
        finalidx = re* M + ce
        visited_id[startnode] = i
        dist[startnode] = 0
        queue = deque([startnode])
        possible = False
        while queue:
            curr = queue.popleft()
            d = dist[curr]
            if curr >= layerkasize:
                m = 1
                idx = curr - layerkasize
            else:
                m = 0
                idx = curr
                
            if idx == finalidx:
                if d <= KK:
                    possible = True
                    break
            if d >= KK:
                continue
            r = idx // M
            c = idx % M
            if G[r][c] == '.':
                nextnode = curr - layerkasize if m == 1 else curr + layerkasize
                if visited_id[nextnode] != i:
                    visited_id[nextnode] = i
                    dist[nextnode] = d + 1
                    queue.append(nextnode)
            if r > 0:
                cel = G[r - 1][c]
                if (m == 0 and cel != 'R') or (m == 1 and cel != 'B'):
                    nextnode = curr - M
                    if visited_id[nextnode] != i:
                        visited_id[nextnode] = i
                        dist[nextnode] = d + 1
                        queue.append(nextnode)
            if r + 1 < N:
                cel = G[r + 1][c]
                if (m == 0 and cel != 'R') or (m == 1 and cel != 'B'):
                    nextnode = curr + M
                    if visited_id[nextnode] != i:
                        visited_id[nextnode] = i
                        dist[nextnode] = d + 1
                        queue.append(nextnode)
            if c > 0:
                cel = G[r][c - 1]
                if (m == 0 and cell != 'R') or (m == 1 and cel != 'B'):
                    nextnode = curr - 1
                    if visited_id[nextnode] != i:
                        visited_id[nextnode] = i
                        dist[nextnode] = d + 1
                        queue.append(nextnode)
            if c + 1 < M:
                cel = G[r][c + 1]
                if (m == 0 and cel != 'R') or (m == 1 and cel != 'B'):
                    nextnode = curr + 1
                    if visited_id[nextnode] != i:
                        visited_id[nextnode] = i
                        dist[nextnode] = d + 1
                        queue.append(nextnode)
        
        if possible:
            results.append("YES")
        else:
            results.append("NO")
            
    return results

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
