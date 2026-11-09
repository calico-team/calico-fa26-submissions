import sys

def solve(N,M,Q,G,start,end):
    comp = [[-1]*M for _ in range(N)]
    num = 0
    moves = [(-1,0), (1,0), (0,-1), (0,1)]
    for r in range(N):
        for c in range(M):
            if comp[r][c] != -1:
                continue
            comp[r][c] = num
            stack = [(r,c)]
            while stack:
                x,y = stack.pop()
                a = G[x][y]
                for dx,dy in moves:
                    nx,ny = x+dx,y+dy
                    if nx <0 or nx >=N or ny <0 or ny >=M:
                        continue
                    if comp[nx][ny] != -1:
                        continue
                    b = G[nx][ny]
                    if a != b:
                        continue
                    comp[nx][ny] = num
                    stack.append((nx,ny))
            num += 1
    ans = []
    for i in range(Q):
        r1,c1 = start[i]
        r2,c2 = end[i]
        if comp[r1][c1] == comp[r2][c2]:
            ans.append("YES")
        else:
            ans.append("NO")
    return ans

def main():
    input = sys.stdin.buffer.readline
    T = int(input())

    for _ in range(T):
        N,M,Q = map(int,input().split())
        G = [input().decode().strip() for _ in range(N)]
        start,end = [],[]

        for _ in range(Q):
            r1,c1,r2,c2 = map(int,input().split())
            start.append((r1,c1))
            end.append((r2,c2))

        ans = solve(N,M,Q,G,start,end)
        sys.stdout.write("\n".join(ans) + "\n")

if __name__ == "__main__":
    main()