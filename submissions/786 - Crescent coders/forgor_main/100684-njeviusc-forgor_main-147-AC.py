
import sys

def solve():
    input = sys.stdin.readline

phase = input().strip()

while not phase:
    phase = input().strip()

line = input().strip()

while not line:
    line = input().strip()

n = int(line)

if phase == "FIRST":
        graph = [[] for _ in range(n + 1)]

        for _ in range(n - 1):
            u, v = map(int, input().split())
            graph[u].append(v)
            graph[v].append(u)

        # Find parent of each node using DFS
        parent = [0] * (n + 1)
        stack = [1]
        parent[1] = -1

        while stack:
            u = stack.pop()

            for v in graph[u]:
                if v != parent[u]:
                    parent[v] = u
                    stack.append(v)

        # Store all parents plus one XOR checksum
        answer = [0] * n

        for v in range(2, n + 1):
            answer[v - 1] = parent[v]
            answer[0] ^= parent[v]

        print(*answer)

else:
        a = list(map(int, input().split()))

        # Recover the missing value using XOR
        if a[0] != -1:
            missing = a[0]

            for x in a[1:]:
                if x != -1:
                    missing ^= x

            for i in range(1, n):
                if a[i] == -1:
                    a[i] = missing
                    break

        # Reconstruct the original tree
        for v in range(2, n + 1):
            print(a[v - 1], v)


if __name__ == "__main__":
    solve()
