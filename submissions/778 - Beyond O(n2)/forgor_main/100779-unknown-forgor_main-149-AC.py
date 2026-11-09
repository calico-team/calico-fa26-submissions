import sys

input = sys.stdin.buffer.readline
MOD = 1_000_000

phase = input().strip().decode()

if phase == "FIRST":
    n = int(input())
    graph = [[] for _ in range(n)]

    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        graph[u].append(v)
        graph[v].append(u)

    parent = [0] * n
    seen = [False] * n
    seen[0] = True
    stack = [0]

    while stack:
        v = stack.pop()
        for u in graph[v]:
            if not seen[u]:
                seen[u] = True
                parent[u] = v + 1
                stack.append(u)

    data = parent[1:]
    data.append(sum(data) % MOD)
    sys.stdout.write(" ".join(map(str, data)) + "\n")

else:  # SECOND
    n = int(input())
    values = list(map(int, input().split()))

    missing = -1
    for i in range(n - 1):
        if values[i] == -1:
            missing = i
            break

    if missing != -1:
        known_sum = 0
        for i in range(n - 1):
            if i != missing:
                known_sum += values[i]
        values[missing] = (values[n - 1] - known_sum) % MOD

    output = []
    for child in range(1, n):
        output.append(f"{values[child - 1]} {child + 1}")

    sys.stdout.write("\n".join(output) + "\n")