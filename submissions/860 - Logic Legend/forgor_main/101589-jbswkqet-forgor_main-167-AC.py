# Source: https://usaco.guide/general/io

import sys

def main():
    data = sys.stdin.buffer.read().split()
    phase = data[0].decode()
    n = int(data[1])

    if phase == "FIRST":
        adj = [[] for _ in range(n)]
        pos = 2

        for _ in range(n - 1):
            u = int(data[pos]) - 1
            v = int(data[pos + 1]) - 1
            pos += 2
            adj[u].append(v)
            adj[v].append(u)

        parent = [-1] * n
        parent[0] = 0
        stack = [0]

        while stack:
            u = stack.pop()
            for v in adj[u]:
                if parent[v] == -1:
                    parent[v] = u
                    stack.append(v)

        encoded = [0] * n
        checksum = 0

        for v in range(1, n):
            encoded[v] = parent[v] + 1
            checksum ^= encoded[v]

        encoded[0] = checksum
        print(*encoded)

    else:
        encoded = list(map(int, data[2:2 + n]))
        missing = encoded.index(-1)

        if missing == 0:
            for v in range(1, n):
                print(v + 1, encoded[v])
        else:
            checksum = encoded[0]
            for v in range(1, n):
                if v != missing:
                    checksum ^= encoded[v]

            encoded[missing] = checksum

            for v in range(1, n):
                print(v + 1, encoded[v])

if __name__ == "__main__":
    main()

