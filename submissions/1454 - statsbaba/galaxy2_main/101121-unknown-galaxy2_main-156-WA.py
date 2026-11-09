import sys

# min-plus matrix multiplication (like Floyd-Warshall but for distance matrices)
def mat_mul(A, B, S, INF):
    C = [INF] * (S * S)
    for i in range(S):
        iS = i * S
        for k in range(S):
            aik = A[iS + k]
            if aik == INF:
                continue
            kS = k * S
            for j in range(S):
                bkj = B[kS + j]
                if bkj == INF:
                    continue
                val = aik + bkj
                if val < C[iS + j]:
                    C[iS + j] = val
    return C

# vector times matrix using min-plus
def vec_mat_mul(vec, mat, S, INF):
    res = [INF] * S
    for v in range(S):
        if vec[v] == INF:
            continue
        vS = v * S
        for w in range(S):
            m = mat[vS + w]
            if m == INF:
                continue
            val = vec[v] + m
            if val < res[w]:
                res[w] = val
    return res

# BFS on a contiguous range of columns
def bfs_range(N, c_start, c_end, active_blue, active_red, is_normal, start_r, start_c, start_m):
    num_cols = c_end - c_start + 1
    total_states = num_cols * 2 * N
    dist = [-1] * total_states
    start_local = (start_c - c_start) * (2 * N) + start_r * 2 + start_m
    dist[start_local] = 0
    queue = [start_local]
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        d = dist[u]
        col_offset = u // (2 * N)
        rem = u % (2 * N)
        r = rem // 2
        m = rem % 2
        c = c_start + col_offset

        # move up
        if r > 0:
            if (m == 0 and active_blue[r-1][c]) or (m == 1 and active_red[r-1][c]):
                v = col_offset * (2 * N) + (r-1) * 2 + m
                if dist[v] == -1:
                    dist[v] = d + 1
                    queue.append(v)
        # move down
        if r < N - 1:
            if (m == 0 and active_blue[r+1][c]) or (m == 1 and active_red[r+1][c]):
                v = col_offset * (2 * N) + (r+1) * 2 + m
                if dist[v] == -1:
                    dist[v] = d + 1
                    queue.append(v)
        # move left
        if c > c_start:
            if (m == 0 and active_blue[r][c-1]) or (m == 1 and active_red[r][c-1]):
                v = (col_offset - 1) * (2 * N) + r * 2 + m
                if dist[v] == -1:
                    dist[v] = d + 1
                    queue.append(v)
        # move right
        if c < c_end:
            if (m == 0 and active_blue[r][c+1]) or (m == 1 and active_red[r][c+1]):
                v = (col_offset + 1) * (2 * N) + r * 2 + m
                if dist[v] == -1:
                    dist[v] = d + 1
                    queue.append(v)
        # spin (toggle mode) only on normal tiles
        if is_normal[r][c]:
            v = col_offset * (2 * N) + r * 2 + (1 - m)
            if dist[v] == -1:
                dist[v] = d + 1
                queue.append(v)
    return dist

# distance between two states using block decomposition
def get_distance(r_a, c_a, m_a, r_b, c_b, m_b, N, M, B, num_blocks, S,
                 active_blue, active_red, is_normal, P_list, st, INF):
    if c_a > c_b:
        r_a, c_a, m_a, r_b, c_b, m_b = r_b, c_b, m_b, r_a, c_a, m_a
    block_a = c_a // B
    block_b = c_b // B
    if block_a == block_b:
        dist = bfs_range(N, c_a, c_b, active_blue, active_red, is_normal, r_a, c_a, m_a)
        end_local = (c_b - c_a) * (2 * N) + r_b * 2 + m_b
        d = dist[end_local]
        return d if d != -1 else INF
    else:
        end_col_a = min((block_a + 1) * B - 1, M - 1)
        dist_left_bfs = bfs_range(N, c_a, end_col_a, active_blue, active_red, is_normal, r_a, c_a, m_a)
        dist_left = [INF] * S
        col_offset = end_col_a - c_a
        base = col_offset * S
        for r in range(N):
            for m in range(2):
                idx = r * 2 + m
                local_idx = base + idx
                d = dist_left_bfs[local_idx]
                if d != -1:
                    dist_left[idx] = d

        start_col_b = block_b * B
        dist_right_bfs = bfs_range(N, start_col_b, c_b, active_blue, active_red, is_normal, r_b, c_b, m_b)
        dist_right = [INF] * S
        for r in range(N):
            for m in range(2):
                idx = r * 2 + m
                d = dist_right_bfs[idx]
                if d != -1:
                    dist_right[idx] = d

        start_next = (block_a + 1) * B
        cost1 = [INF] * S
        for r in range(N):
            for m in range(2):
                u_idx = r * 2 + m
                if dist_left[u_idx] == INF:
                    continue
                if (m == 0 and active_blue[r][end_col_a] and active_blue[r][start_next]) or \
                   (m == 1 and active_red[r][end_col_a] and active_red[r][start_next]):
                    cost1[u_idx] = dist_left[u_idx] + 1

        if block_a + 1 <= block_b - 1:
            l = block_a + 1
            r = block_b - 1
            length = r - l + 1
            k = length.bit_length() - 1
            A = st[k][l]
            B_mat = st[k][r - (1 << k) + 1]
            P_comp = mat_mul(A, B_mat, S, INF)
            cost2 = vec_mat_mul(cost1, P_comp, S, INF)
        else:
            cost2 = cost1

        total = INF
        for w in range(S):
            if cost2[w] != INF and dist_right[w] != INF:
                val = cost2[w] + dist_right[w]
                if val < total:
                    total = val
        return total

def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out = []
    INF = 10**9
    for _ in range(T):
        N = int(next(it))
        M = int(next(it))
        Q = int(next(it))
        grid = []
        for _ in range(N):
            grid.append(next(it))

        active_blue = [[False] * M for _ in range(N)]
        active_red = [[False] * M for _ in range(N)]
        is_normal = [[False] * M for _ in range(N)]
        for r in range(N):
            row = grid[r]
            for c in range(M):
                ch = row[c]
                if ch == '.':
                    active_blue[r][c] = True
                    active_red[r][c] = True
                    is_normal[r][c] = True
                elif ch == 'B':
                    active_blue[r][c] = True
                elif ch == 'R':
                    active_red[r][c] = True

        queries = []
        for _ in range(Q):
            r1 = int(next(it)); c1 = int(next(it))
            r2 = int(next(it)); c2 = int(next(it))
            K = int(next(it))
            queries.append((r1, c1, r2, c2, K))

        B = 32
        num_blocks = (M + B - 1) // B
        S = 2 * N

        P_list = []
        for b in range(num_blocks - 1):
            start_col = b * B
            next_start_col = (b + 1) * B
            c_start = start_col
            c_end = next_start_col
            P_mat = [INF] * (S * S)
            for u_r in range(N):
                for u_m in range(2):
                    if u_m == 0 and not active_blue[u_r][start_col]:
                        continue
                    if u_m == 1 and not active_red[u_r][start_col]:
                        continue
                    u_idx = u_r * 2 + u_m
                    dist = bfs_range(N, c_start, c_end, active_blue, active_red, is_normal, u_r, start_col, u_m)
                    col_offset = next_start_col - c_start
                    base = col_offset * S
                    for v_r in range(N):
                        for v_m in range(2):
                            if v_m == 0 and not active_blue[v_r][next_start_col]:
                                continue
                            if v_m == 1 and not active_red[v_r][next_start_col]:
                                continue
                            v_idx = v_r * 2 + v_m
                            local_idx = base + v_idx
                            d = dist[local_idx]
                            if d != -1:
                                P_mat[u_idx * S + v_idx] = d
            P_list.append(P_mat)

        num_P = len(P_list)
        st = None
        if num_P > 0:
            st = []
            st.append(P_list)
            k = 1
            while (1 << k) <= num_P:
                prev = st[k-1]
                curr_len = num_P - (1 << k) + 1
                curr = [None] * curr_len
                step = 1 << (k-1)
                for i in range(curr_len):
                    A = prev[i]
                    B_mat = prev[i + step]
                    curr[i] = mat_mul(A, B_mat, S, INF)
                st.append(curr)
                k += 1

        for (r1, c1, r2, c2, K) in queries:
            cell_char = grid[r2][c2]
            if cell_char == '.':
                end_modes = [0, 1]
            elif cell_char == 'B':
                end_modes = [0]
            else:
                end_modes = [1]
            min_dist = INF
            for end_m in end_modes:
                d = get_distance(r1, c1, 0, r2, c2, end_m, N, M, B, num_blocks, S,
                                 active_blue, active_red, is_normal, P_list, st, INF)
                if d < min_dist:
                    min_dist = d
            out.append("YES" if min_dist <= K else "NO")
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()