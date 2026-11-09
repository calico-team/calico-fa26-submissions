import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))

        grid = [next(iterator) for _ in range(N)]

        NM = N * M
        grid_flat = "".join(grid)

        active = [False] * (2 * NM)
        for p in range(NM):
            ch = grid_flat[p]
            if ch != "R":
                active[p * 2] = True  
            if ch != "B":
                active[p * 2 + 1] = True  

        neighbors = [[] for _ in range(NM)]
        for r in range(N):
            for c in range(M):
                p = r * M + c
                if r > 0:
                    neighbors[p].append(p - M)
                if r < N - 1:
                    neighbors[p].append(p + M)
                if c > 0:
                    neighbors[p].append(p - 1)
                if c < M - 1:
                    neighbors[p].append(p + 1)

        comp = [-1] * (2 * NM)
        comp_id = 0

        for start_u in range(2 * NM):
            if not active[start_u] or comp[start_u] != -1:
                continue

            q = [start_u]
            comp[start_u] = comp_id
            head = 0

            while head < len(q):
                u = q[head]
                head += 1

                p = u >> 1
                m = u & 1

                if grid_flat[p] == ".":
                    v = u ^ 1
                    if comp[v] == -1:
                        comp[v] = comp_id
                        q.append(v)

                for np in neighbors[p]:
                    v = np * 2 + m
                    if active[v] and comp[v] == -1:
                        comp[v] = comp_id
                        q.append(v)

            comp_id += 1

        for _ in range(Q):
            r_start = int(next(iterator))
            c_start = int(next(iterator))
            r_end = int(next(iterator))
            c_end = int(next(iterator))

            p_start = r_start * M + c_start
            u_start = p_start * 2  

            p_end = r_end * M + c_end
            ch_end = grid_flat[p_end]
            target_m = 1 if ch_end == "R" else 0
            u_end = p_end * 2 + target_m

            if comp[u_start] != -1 and comp[u_start] == comp[u_end]:
                out.append("YES")
            else:
                out.append("NO")

    print("\n".join(out))

if __name__ == "__main__":
    solve()