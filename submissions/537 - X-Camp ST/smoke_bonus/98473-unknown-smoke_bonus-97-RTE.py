from collections import deque

t = int(input())

def isVaild(r, c, good, mode):
    if r < 0:
        return False
    if r >= n:
        return False
    if c < 0:
        return False
    if c >= m:
        return False
    if vis[r][c]:
        return False
    if not good:
        if mode == "B" and ls[r][c] == "R":
            return False
        elif mode == "R" and ls[r][c] == "B":
            return False
        else:
            return True
    return True


for i in range(t):
    n, m, q = map(int, input().split())
    ls = [list(input().strip()) for i in range(n)]

    for i in range(q):
        queue = deque()

        sr, sc, er, ec = map(int, input().split())
        queue.append((sr, sc, "B"))

        vis = [[False] * m for i in range(n)]
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        p = False

        while queue:
            r, c, mode = queue.popleft()

            if r == er and c == ec:
                print("YES")
                p = True
                break

            if ls[r][c] == ".":
                good = True
            else:
                good = False

            for dr, dc in dirs:
                nr = r + dr
                nc = c + dc

                if isVaild(nr, nc, good, mode):
                    vis[nr][nc] = True
                    queue.append((nr, nc, str(ls[nr][nc])))

        if not p:
            print("NO")
