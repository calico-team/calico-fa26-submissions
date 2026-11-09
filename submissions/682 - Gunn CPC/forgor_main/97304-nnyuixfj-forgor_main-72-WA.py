import sys

def solve():
    data = sys.stdin.buffer.read().split()

    mode = data[0].decode()
    n = int(data[1])

    if mode == "FIRST":
        adj = [[] for _ in range(n + 1)]

        idx = 2
        for _ in range(n - 1):
            u = int(data[idx])
            v = int(data[idx + 1])
            idx += 2

            adj[u].append(v)
            adj[v].append(u)

        par = [0] * (n + 1)
        par[1] = 1

        st = [1]

        while st:
            cur = st.pop()

            for nxt in adj[cur]:
                if nxt == par[cur]:
                    continue

                par[nxt] = cur
                st.append(nxt)

        print(*par[2:])

    else:
        parents = list(map(int, data[2:2 + n]))

        for i in range(n - 1):
            print(i + 2, parents[i])


if __name__ == "__main__":
    solve()