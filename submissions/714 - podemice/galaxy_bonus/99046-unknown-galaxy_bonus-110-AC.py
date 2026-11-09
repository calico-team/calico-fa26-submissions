def dfs(rows, cols, game_map, visited, r0, c0, idx):
    to_visit = [(r0, c0)]
    visited[r0][c0] = idx
    while len(to_visit) > 0:
        curr = to_visit.pop()
        candidates = [(curr[0] + 1, curr[1]), (curr[0] - 1, curr[1]), (curr[0], curr[1] + 1), (curr[0], curr[1] - 1)]
        for c in candidates:
            if (c[0] < 0 or c[0] >= rows or c[1] < 0 or c[1] >= cols):
                continue
            if visited[c[0]][c[1]] > 0:
                continue
            curr_cell = game_map[curr[0]][curr[1]]
            cand_cell = game_map[c[0]][c[1]]
            if curr_cell == "." or cand_cell == "." or (curr_cell == cand_cell):
                visited[c[0]][c[1]] = idx
                to_visit.append(c)

def solve(rows, cols, num_queries, game_map, queries):
    visited = [[0 for _ in range(cols)] for _ in range(rows)]

    idx = 1
    for i in range(rows):
        for j in range(cols):
            if visited[i][j] > 0:
                continue
            dfs(rows, cols, game_map, visited, i, j, idx)
            idx += 1

    for query_idx in range(num_queries):
        query = queries[query_idx]
        r0 = query[0]
        c0 = query[1]
        r1 = query[2]
        c1 = query[3]
        if visited[r0][c0] == visited[r1][c1]:
            print("YES")
        else:
            print("NO")


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
