
import sys

# Check the current limit (usually 1000)
# I set it to 5000 but it still has an error...
# Increase recursion limit to 9999 now (hopefully it works)

# LAST ATTEMPT CHANGE IT TO 50000
sys.setrecursionlimit(50000)
# Dylan suggested I use a stack and Im not that familiar with them.

def active(matrix,x,y, mode):
    if matrix[x][y] == '.':
        return True
    if matrix[x][y] == 'B':
        return mode == 0
    if matrix[x][y] == 'R':
        return mode == 1




                    
                    


        


        
def dfs(x, y, mode, id, visited, group, matrix, n, m):
    stack = [(x, y, mode)]
    while stack:

        x, y, mode = stack.pop()

        if visited[x][y][mode]:
            continue
        
        visited[x][y][mode] = True
        group[x][y][mode] = id

        if matrix[x][y] == '.':
            if not visited[x][y][1 - mode]:
                stack.append((x, y, 1 - mode))

        for nx, ny in [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]:
            if 0 <= nx < n and 0 <= ny < m and active(matrix, nx, ny, mode) and not visited[nx][ny][mode]:#unvisited
                stack.append((nx, ny, mode))





def function():
    n, m, q = map(int, input().split()) #n is rows, m is cols, q is qeuries
    matrix = []
    for i in range(n):
        matrix.append(list(input().strip()))

    visited = [[[False, False] for _ in range(m)] for _ in range(n)]
    group = [[[-1, -1] for _ in range(m)] for _ in range(n)]
    id = 0
    for x in range(n):
        for y in range(m):
            for mode in range(0, 2):
                if active(matrix, x, y, mode) and not visited[x][y][mode]:
                    dfs(x, y, mode, id, visited, group, matrix, n, m)
                    id += 1

    answers = []
    for i in range(q):
        sx, sy, ex, ey = map(int, input().split())

        possible = False

        for sm in range(2):
            for em in range(2):
                if (active(matrix, sx, sy, sm)
                    and active(matrix, ex, ey, em)
                    and group[sx][sy][sm] == group[ex][ey][em]):
                    possible = True

        answers.append("YES" if possible else "NO")

    print("\n".join(answers))












t = int(input())
for i in range(t):
    function()