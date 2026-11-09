from collections import deque
import sys

input = sys.stdin.readline
MOD = 1000001

phase = input().strip()
n = int(input())

if phase == "FIRST":
    graph = [[] for _ in range(n + 1)]

    for _ in range(n - 1):
        a, b = map(int, input().split())
        graph[a].append(b)
        graph[b].append(a)

    parent = [0] * (n + 1)
    visited = [False] * (n + 1)

    queue = deque([1])
    visited[1] = True

    while queue:
        current = queue.popleft()

        for nxt in graph[current]:
            if not visited[nxt]:
                visited[nxt] = True
                parent[nxt] = current
                queue.append(nxt)

    data = parent[2:]
    data.append(sum(data) % MOD)

    print(*data)

else:
    encoded = list(map(int, input().split()))

    if encoded[-1] == -1:
        encoded[-1] = sum(encoded[:-1]) % MOD
    else:
        lost = encoded.index(-1)

        known_sum = sum(encoded[:-1]) + 1
        encoded[lost] = (encoded[-1] - known_sum) % MOD

    result = []

    for node in range(2, n + 1):
        result.append(f"{node} {encoded[node - 2]}")

    sys.stdout.write("\n".join(result) + "\n")
