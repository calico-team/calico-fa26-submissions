import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    idx = 0
    T = int(data[idx])
    idx += 1

    out = []
    for _ in range(T):
        N = int(data[idx])
        M = int(data[idx + 1])
        Q = int(data[idx + 2])
        idx += 3

        grid = data[idx : idx + N]
        idx += N

        parent = list(range(2 * N * M))

        def find(i):
            if parent[i] != i:
                parent[i] = find(parent[i])
            return parent[i]

        def union(i, j):
            root_i, root_j = find(i), find(j)
            if root_i != root_j:
                parent[root_i] = root_j

        for r in range(N):
            for c in range(M):
                cell = grid[r][c]
                u_blue = (r * M + c) * 2
                u_red = u_blue + 1

                if cell == ".":
                    union(u_blue, u_red)

                if r + 1 < N:
                    v_blue = ((r + 1) * M + c) * 2
                    v_red = v_blue + 1
                    down = grid[r + 1][c]
                    if cell in ".B" and down in ".B":
                        union(u_blue, v_blue)
                    if cell in ".R" and down in ".R":
                        union(u_red, v_red)

                if c + 1 < M:
                    v_blue = (r * M + (c + 1)) * 2
                    v_red = v_blue + 1
                    right = grid[r][c + 1]
                    if cell in ".B" and right in ".B":
                        union(u_blue, v_blue)
                    if cell in ".R" and right in ".R":
                        union(u_red, v_red)

        for _ in range(Q):
            rs, cs, re, ce = (
                int(data[idx]),
                int(data[idx + 1]),
                int(data[idx + 2]),
                int(data[idx + 3]),
            )
            idx += 4

            start_node = (rs * M + cs) * 2
            end_blue = (re * M + ce) * 2
            end_red = end_blue + 1
            root_start = find(start_node)

            target = grid[re][ce]
            can_blue = target in ".B" and (root_start == find(end_blue))
            can_red = target in ".R" and (root_start == find(end_red))

            out.append("YES" if can_blue or can_red else "NO")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()