def read_your_input():
    phase = input().strip()
    n = int(input())

    if phase == "FIRST":
        adj = [[] for _ in range(n)]

        for i in range(n - 1):
            u, v = map(int, input().split())

            u -= 1
            v -= 1

            adj[u].append(v)
            adj[v].append(u)

        parent = [-1] * n
        stack = [0]

        while stack:
            node = stack.pop()

            for child in adj[node]:
                if child != parent[node]:
                    parent[child] = node
                    stack.append(child)

        answer = [0] * n

        for i in range(1, n):
            answer[i] = parent[i] + 1
            answer[0] ^= answer[i]

        print(*answer)

    else:
        answer = list(map(int, input().split()))

        missing = answer.index(-1)

        if missing != 0:
            value = answer[0]

            for i in range(1, n):
                if i != missing:
                    value ^= answer[i]

            answer[missing] = value

        for i in range(1, n):
            print(answer[i], i + 1)


read_your_input()