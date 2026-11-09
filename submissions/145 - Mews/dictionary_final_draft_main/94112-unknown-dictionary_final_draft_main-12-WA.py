def solve():
    import sys
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))

        dinosauraus = [0] * N
        ans = [0] * N

        for i in range(N):
            if ans[i] != 0:
                continue

            path = []
            pos = {}
            cur = i

            while cur not in pos and ans[cur] == 0:
                pos[cur] = len(path)
                path.append(cur)
                cur = A[cur] - 1

            if ans[cur] != 0:
                base = ans[cur]
                for node in reversed(path):
                    base ^= V[node]
                    ans[node] = max(V[node], base)
            else:
                cycle_start = pos[cur]
                cycle = path[cycle_start:]

                prefix = 0
                for node in cycle:
                    prefix ^= V[node]

                cycle_xor = prefix

                if cycle_xor == 0:
                    for node in cycle:
                        ans[node] = 0
                else:
                    for node in cycle:
                        ans[node] = cycle_xor

                for node in reversed(path[:cycle_start]):
                    nxt = A[node] - 1
                    ans[node] = max(V[node], V[node] ^ ans[nxt])

            for node in path[:cycle_start] if cur not in pos else path:
                pass

        print(*ans)


def read_your_input():
    solve()


if __name__ == "__main__":
    read_your_input()