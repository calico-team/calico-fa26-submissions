import sys

INF = 10**18

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    T = int(next(iterator))
    
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        grid = [next(iterator) for _ in range(N)]
        K_states = 2 * N
        
        base_dist = [[[INF] * K_states for _ in range(K_states)] for _ in range(M)]
        
        for c in range(M):
            dist = base_dist[c]
            for i in range(K_states):
                dist[i][i] = 0
                
            for r in range(N):
                if grid[r][c] == '.':
                    u = 0 * N + r
                    v = 1 * N + r
                    dist[u][v] = 1
                    dist[v][u] = 1
                    
            for r in range(N):
                for mode in range(2):
                    u = mode * N + r
                    if grid[r][c] == '.' or (mode == 0 and grid[r][c] == 'B') or (mode == 1 and grid[r][c] == 'R'):
                        for nr in [r - 1, r + 1]:
                            if 0 <= nr < N:
                                if grid[nr][c] == '.' or (mode == 0 and grid[nr][c] == 'B') or (mode == 1 and grid[nr][c] == 'R'):
                                    v = mode * N + nr
                                    dist[u][v] = min(dist[u][v], 1)
                                    
            for k in range(K_states):
                for i in range(K_states):
                    for j in range(K_states):
                        if dist[i][k] + dist[k][j] < dist[i][j]:
                            dist[i][j] = dist[i][k] + dist[k][j]

        def combine(A, B, c_mid):
            res = [[INF] * K_states for _ in range(K_states)]
            valid_transitions = []
            for r in range(N):
                for mode in range(2):
                    if (grid[r][c_mid] == '.' or (mode == 0 and grid[r][c_mid] == 'B') or (mode == 1 and grid[r][c_mid] == 'R')) and \
                       (grid[r][c_mid+1] == '.' or (mode == 0 and grid[r][c_mid+1] == 'B') or (mode == 1 and grid[r][c_mid+1] == 'R')):
                        u = mode * N + r
                        valid_transitions.append(u)
            
            for i in range(K_states):
                for u in valid_transitions:
                    if A[i][u] == INF:
                        continue
                    for j in range(K_states):
                        if B[u][j] == INF:
                            continue
                        cost = A[i][u] + 1 + B[u][j]
                        if cost < res[i][j]:
                            res[i][j] = cost
            return res

        tree_size = 4 * M
        tree = [None] * tree_size
        
        def build(node, start, end):
            if start == end:
                tree[node] = base_dist[start]
                return
            mid = (start + end) // 2
            build(2 * node, start, mid)
            build(2 * node + 1, mid + 1, end)
            tree[node] = combine(tree[2 * node], tree[2 * node + 1], mid)

        build(1, 0, M - 1)

        def query(node, start, end, l, r):
            if l <= start and end <= r:
                return tree[node]
            mid = (start + end) // 2
            if r <= mid:
                return query(2 * node, start, mid, l, r)
            if l > mid:
                return query(2 * node + 1, mid + 1, end, l, r)
                
            left_res = query(2 * node, start, mid, l, r)
            right_res = query(2 * node + 1, mid + 1, end, l, r)
            return combine(left_res, right_res, mid)

        for _ in range(Q):
            r_start = int(next(iterator))
            c_start = int(next(iterator))
            r_end = int(next(iterator))
            c_end = int(next(iterator))
            K = int(next(iterator))
            
            start_state = 0 * N + r_start
            is_reversed = False
            if c_start > c_end:
                c_start, c_end = c_end, c_start
                r_start, r_end = r_end, r_start
                start_state = 0 * N + r_end
                is_reversed = True
                
            res_matrix = query(1, 0, M - 1, c_start, c_end)
            
            min_dist = INF
            if not is_reversed:
                min_dist = min(res_matrix[start_state][0 * N + r_end], res_matrix[start_state][1 * N + r_end])
            else:
                min_dist = min(res_matrix[0 * N + r_start][start_state], res_matrix[1 * N + r_start][start_state])
                
            if min_dist <= K:
                print("YES")
            else:
                print("NO")

if __name__ == "__main__":
    solve()
