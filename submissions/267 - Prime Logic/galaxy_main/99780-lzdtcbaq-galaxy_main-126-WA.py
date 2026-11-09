import sys

def solve(N,M,Q,G,start,end):
    group = [[-1] * M for _ in range(N)]
    number = 0
    for r in range(N):
        for c in range(M):
            if group[r][c] != -1:
                continue
            group[r][c] = number
            stack = [(r,c)]
            while stack:
                x,y = stack.pop()
                color = G[x][y]
                for nx,ny in ((x-1,y), (x+1,y), (x,y-1), (x,y+1)):
                    if not (0 <= nx <N and 0 <= ny < M):
                        continue
                    if group[nx][ny] != -1:
                        continue
                    other = G[nx][ny]
                    if color == "R" and other == "B":
                        continue
                    group[nx][ny] =number
                    stack.append((nx,ny))
            number += 1
    ans = []
    for (r1,c1), (r2,c2) in zip(start,end):
        if group[r1][c1] == group[r2][c2]:
            ans.append("YES")
        else:
            ans.append("NO")
    return ans

def main():
    input = sys.stdin.buffer.readline
    T = int(input())
    for _ in range(T):
        N,M,Q = map(int, input().split())
        G = [input().decode().strip() for _ in range(N)]
        start,end = [], []
        for _ in range(Q):
            r1,c1,r2,c2 = map(int,input().split())
            start.append((r1,c1))
            end.append((r2,c2))
        sys.stdout.write("\n".join(solve(N,M,Q,G,start, end)))
        sys.stdout.write("\n")

if __name__ == "__main__":
    main()