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
    comp = [[-1]*M for _ in range(N)]
    comps = 1
    for row in range(N):
        for col in range(M):
            if comp[row][col] !=-1: continue
            comp[row][col] = comps
            stack = [(row, col)]
            while stack:
                r, c = stack.pop()
                for dx, dy in dirs:
                    nr, nc = r+dx, c+dy
                    if nr < 0 or nr >= N or nc < 0 or nc >= M: continue
                    if comp[nr][nc] != -1: continue
                    if grid[nr][nc] == grid[r][c] or grid[nr][nc] == '.' or grid[r][c] == '.':
                        comp[nr][nc] = comps
                        stack.append((nr, nc))
            comps += 1
    for _ in range(Q):
        sr,sc,tr,tc = mapInt()
        if comp[sr][sc] == comp[tr][tc]:
            printYes()
        else:
            printNo()

# ============================== MAIN DRIVER ==================================== #

def main():
    for _ in range(intInp()): solve()

# ============================== EXECUTION ====================================== #

if __name__ == "__main__":
    main()