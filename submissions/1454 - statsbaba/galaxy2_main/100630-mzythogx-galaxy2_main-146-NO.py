def bfs(start_r, start_c, start_mode, L, R, N, grid, dist_array, offset):
    # dist_array is a list of size total_local_states, we will fill from offset to offset+total_local_states
    total_local = (R - L + 1) * N * 2
    # We can use a local array for distances, or directly write to dist_array[offset + local_id]
    # We'll use a separate list for current BFS to avoid offset arithmetic in inner loop? 
    # It's better to have a local list `d` of size total_local, initialized to -1.
    d = [-1] * total_local
    start_local = ((start_c - L) * N + start_r) * 2 + start_mode
    d[start_local] = 0
    q = deque([ (start_r, start_c, start_mode) ])  # or use local_id and decode
    # Actually, we can just store local_id in queue and decode when needed.
    # Decoding: c = L + (id // (N*2)); rem = id % (N*2); r = rem // 2; mode = rem % 2.
    # To avoid division, we can store (r,c,mode) directly, or precompute arrays for r,c,mode from id.
    # Since total_local is not too large, we can just use (r,c,mode) in queue.
    while q:
        r, c, mode = q.popleft()
        current_dist = d[((c - L) * N + r) * 2 + mode]
        # Try spin
        if grid[r][c] == '.':
            nmode = 1 - mode
            nid = ((c - L) * N + r) * 2 + nmode
            if d[nid] == -1:
                d[nid] = current_dist + 1
                q.append((r, c, nmode))
        # Try 4 moves
        for dr, dc in ((1,0), (-1,0), (0,1), (0,-1)):
            nr, nc = r + dr, c + dc
            if L <= nc <= R and 0 <= nr < N:
                # check active in current mode
                tile = grid[nr][nc]
                if tile == '.' or (mode == 0 and tile == 'B') or (mode == 1 and tile == 'R'):
                    nid = ((nc - L) * N + nr) * 2 + mode
                    if d[nid] == -1:
                        d[nid] = current_dist + 1
                        q.append((nr, nc, mode))
    # Copy d into dist_array at offset
    dist_array[offset:offset+total_local] = d