# ██████╗ ███████╗ █████╗ ██████╗     ██╗  ██╗██╗██╗     ██╗     ███████╗██████╗
# ██╔══██╗██╔════╝██╔══██╗██╔══██╗    ██║ ██╔╝██║██║     ██║     ██╔════╝██╔══██╗
# ██║  ██║█████╗  ███████║██║  ██║    █████╔╝ ██║██║     ██║     █████╗  ██████╔╝
# ██║  ██║██╔══╝  ██╔══██║██║  ██║    ██╔═██╗ ██║██║     ██║     ██╔══╝  ██╔══██╗
# ██████╔╝███████╗██║  ██║██████╔╝    ██║  ██╗██║███████╗███████╗███████╗██║  ██║
# ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝     ╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝
#          ☠  D E A D   K I L L E R'S   T E M P L A T E  ☠

# ============================== IMPORTS ================================= #
import sys
from collections import defaultdict,Counter,deque

# ============================== CONSTANTS ================================= #
posINF = float('inf')
negINF = float('-inf')

# ============================== ULTRA FAST IO ================================= #

input = sys.stdin.readline
write = sys.stdout.write

def inp(): return input().strip()
def intInp(): return int(inp())
def mapInt(): return map(int, inp().split())
def mapStr(): return map(str, inp().split())
def listInt(): return list(map(int, inp().split()))
def listStr(): return list(map(str, inp().split()))
def listFloat(): return list(map(float, inp().split()))
def digsOfNum(X): return list(map(int,list(str(X))))

# Fast Output Helpers
def printLine(x): write(str(x) + "\n")
def printArr(arr): write(" ".join(map(str, arr)) + "\n")
def printYes(): write("YES\n")
def printNo(): write("NO\n")


# ============================== SOLVE FUNCTION ================================= #
dirs = [(0,1),(1,0),(0,-1),(-1,0)]
def solve():
    N,M,Q = mapInt()
    grid = [list(inp()) for _ in range(N)]
    pos = dict()
    for i in range(N):
        for j in range(M):
            pos[(i,j)] = -1
    def dfs(r,c,colorMode):
        if r == N-1 and c == M-1: 
            pos[(r,c)] = True
            return True
        org = grid[r][c]
        grid[r][c] = 'X'
        mx = 0
        for dr,dc in dirs:
            newR,newC = r+dr,c+dc
            if newR < 0 or newR >= N or newC < 0 or newC >= M: continue
            if grid[r+dr][c+dc] == '.':
                mx = max(mx, dfs(r+dr,c+dc,colorMode))
            elif grid[r+dr][c+dc] == "R" and colorMode == "R":
                mx = max(mx, dfs(r+dr,c+dc,colorMode))
            elif grid[r+dr][c+dc] == "B" and colorMode == "B":
                mx = max(mx, dfs(r+dr,c+dc,colorMode))
            elif org == "." and grid[r+dr][c+dc] in ["R","B"]:
                mx = max(mx, dfs(r+dr,c+dc,grid[r+dr][c+dc]))
        grid[r][c] = org
        pos[(r,c)] = bool(mx)
        return pos[(r,c)]
    for r in range(N):
        for c in range(M):
            if grid[r][c] == '.' and pos[(r,c)] == -1:
                pos [(r,c)] = dfs(r,c,"B")
    for _ in range(Q):
        r,c,dx,dy = mapInt()
        if pos[(r,c)] != -1 and pos[(r,c)]:
            printYes()
        else:
            printNo()

# ============================== MAIN DRIVER ==================================== #

def main():
    for _ in range(intInp()): solve()

# ============================== EXECUTION ====================================== #

if __name__ == "__main__":
    main()