
import sys


def solve():
    data = sys.stdin.buffer.read().split()
    phase = data[0].decode()
    n = int(data[1])

    if phase == "FIRST":
        graph = [[] for _ in range(n + 1)]

        p = 2
        for _ in range(n - 1):
            u = int(data[p])
            v = int(data[p + 1])
            p += 2

            graph[u].append(v)
            graph[v].append(u)

        parent = [0] * (n + 1)
        parent[1] = 1
        stack = [1]

        while stack:
            u = stack.pop()

            for v in graph[u]:
                if v == parent[u]:
                    continue

                parent[v] = u
                stack.append(v)

        ans = [parent[i] for i in range(2, n + 1)]

        check = 0
        for x in ans:
            check ^= x

        ans.extend([check, 0])

        # print(ans)
        print(*ans)

    else:
        a = list(map(int, data[2:2 + n]))

        missing = a.index(-1)

        if missing < n - 1:
            value = a[n - 1]

            for i in range(n - 1):
                if i != missing:
                    value ^= a[i]

            a[missing] = value

        for i in range(n - 1):
            # print(i, a[i])
            print(i + 2, a[i])


if __name__ == "__main__":
    solve()

    