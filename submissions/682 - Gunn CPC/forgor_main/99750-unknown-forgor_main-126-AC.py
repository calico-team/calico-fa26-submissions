import sys
from collections import deque

def main():
    data = sys.stdin.read().split()
    phase, n = data[0], int(data[1])

    if phase == "FIRST":
        adj = [[] for _ in range(n + 1)]
        for k in range(n - 1):
            u = int(data[2 + 2 * k]); v = int(data[3 + 2 * k])
            adj[u].append(v)
            adj[v].append(u)

        par = [0] * (n + 1)
        seen = [False] * (n + 1)
        seen[1] = True
        q = deque([1])
        while q:
            x = q.popleft()
            for y in adj[x]:
                if not seen[y]:
                    seen[y] = True
                    par[y] = x
                    q.append(y)

        chk = 0
        for i in range(2, n + 1):
            chk ^= par[i]
        print(chk, *par[2:])

    else:
        a = list(map(int, data[2:2 + n]))
        if a[0] != -1:
            miss = a.index(-1) if -1 in a else -1
            if miss != -1:
                x = a[0]
                for i in range(1, n):
                    if i != miss:
                        x ^= a[i]
                a[miss] = x
        print("\n".join(f"{i + 1} {a[i]}" for i in range(1, n)))

if __name__ == "__main__":
    main()