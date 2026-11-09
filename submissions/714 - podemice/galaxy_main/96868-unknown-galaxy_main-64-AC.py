def solve(rows, cols, num_queries, game_map, queries):
    dp = [[0 for _ in range(cols)] for _ in range(rows)]
    seen = {(rows - 1, cols - 1)}
    to_visit = [(rows - 1, cols - 1)]
    curr = None
    while len(to_visit) > 0:
        curr = to_visit.pop()
        dp[curr[0]][curr[1]] = 1
        seen.add(curr)

        candidates = [(curr[0] + 1, curr[1]), (curr[0] - 1, curr[1]), (curr[0], curr[1] + 1), (curr[0], curr[1] - 1)]
        for c in candidates:
            if c in seen:
                continue
            if (c[0] < 0 or c[0] >= rows or c[1] < 0 or c[1] >= cols):
                continue
            curr_cell = game_map[curr[0]][curr[1]]
            cand_cell = game_map[c[0]][c[1]]
            if curr_cell == "." or cand_cell == "." or (curr_cell == cand_cell):
                seen.add(c)
                to_visit.append(c)

    for query_idx in range(num_queries):
        query = queries[query_idx]
        r0 = query[0]
        c0 = query[1]
        r1 = query[2]
        c1 = query[3]
        if dp[r0][c0] == 0:
            print("NO")
        else:
            print("YES")


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = input().split(" ")
        gamemap = []
        for _ in range(int(N)):
            gamemap.append(list(input()))
        queries = []
        for _ in range(int(Q)):
            queries.append(list(map(int, input().split(" "))))
        solve(int(N), int(M), int(Q), gamemap, queries)

main()
