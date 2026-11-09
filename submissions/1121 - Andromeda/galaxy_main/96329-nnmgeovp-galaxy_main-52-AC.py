def bfs(board, goal):
    seen = {goal}
    layer = [goal]

    while layer:
        next_layer = []
        for r, c in layer:
            for cell in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                if cell not in board or cell in seen:
                    continue
                if board[r, c] + board[cell] in ("RB", "BR"):
                    continue
                seen.add(cell)
                next_layer.append(cell)
        layer = next_layer

    return seen


for case in range(int(input())):
    rows, cols, queries = map(int, input().split())
    board = {}
    for r in range(rows):
        for c, tile in enumerate(input().strip()):
            board[r, c] = tile

    reachable = {}
    for query in range(queries):
        sr, sc, er, ec = map(int, input().split())
        goal = (er, ec)
        if goal not in reachable:
            area = bfs(board, goal)
            for cell in area:
                reachable[cell] = area

        print("YES" if (sr, sc) in reachable[goal] else "NO")


        
