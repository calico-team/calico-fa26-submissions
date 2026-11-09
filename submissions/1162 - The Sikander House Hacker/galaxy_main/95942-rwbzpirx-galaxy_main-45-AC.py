import sys

def main():
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
        queries = []
        for _ in range(Q):
            r_s = int(next(iterator))
            c_s = int(next(iterator))
            r_e = int(next(iterator))
            c_e = int(next(iterator))
            queries.append((r_s, c_s, r_e, c_e))
        
        parent = list(range(2 * N * M))
        
        def find(i):
            path = []
            while parent[i] != i:
                path.append(i)
                i = parent[i]
            for p in path:
                parent[p] = i
            return i

        def union(i, j):
            root_i = find(i)
            root_j = find(j)
            if root_i != root_j:
                parent[root_i] = root_j

        def get_id(r, c, m):
            return (r * M + c) * 2 + m

        for r in range(N):
            for c in range(M):
                for m in range(2):
                    tile = grid[r][c]
                    active = (tile == '.') or (tile == 'B' and m == 0) or (tile == 'R' and m == 1)
                    if not active:
                        continue
                    for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < M:
                            ntile = grid[nr][nc]
                            nactive = (ntile == '.') or (ntile == 'B' and m == 0) or (ntile == 'R' and m == 1)
                            if nactive:
                                union(get_id(r, c, m), get_id(nr, nc, m))

        for r in range(N):
            for c in range(M):
                if grid[r][c] == '.':
                    union(get_id(r, c, 0), get_id(r, c, 1))

        output = []
        for r_s, c_s, r_e, c_e in queries:
            s_id = get_id(r_s, c_s, 0)
            e_id_0 = get_id(r_e, c_e, 0)
            e_id_1 = get_id(r_e, c_e, 1)
            if find(s_id) == find(e_id_0) or find(s_id) == find(e_id_1):
                output.append("YES")
            else:
                output.append("NO")
        sys.stdout.write("\n".join(output) + "\n")

if __name__ == '__main__':
    main()