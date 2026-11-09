
def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    B = max(1, max(V).bit_length())
    ans = [0] * N
    rev = [[] for _ in range(N)]
    indeg = [0] * N

    for i, a in enumerate(A):
        rev[a].append(i)
        indeg[a] += 1

    from collections import deque

    q = deque(i for i in range(N) if indeg[i] == 0)
    removed = [False] * N

    while q:
        u = q.popleft()
        removed[u] = True
        p = A[u]
        indeg[p] -= 1
        if indeg[p] == 0:
            q.append(p)

    class Trie:
        def __init__(self):
            self.left = [-1]
            self.right = [-1]
            self.cnt = [0]

        def add(self, x, delta):
            node = 0
            self.cnt[node] += delta

            for b in range(B - 1, -1, -1):
                bit = (x >> b) & 1
                arr = self.right if bit else self.left
                nxt = arr[node]

                if nxt == -1:
                    nxt = len(self.cnt)
                    arr[node] = nxt
                    self.left.append(-1)
                    self.right.append(-1)
                    self.cnt.append(0)

                node = nxt
                self.cnt[node] += delta

        def query(self, x):
            if self.cnt[0] == 0:
                return 0

            node = 0
            result = 0

            for b in range(B - 1, -1, -1):
                bit = (x >> b) & 1

                preferred = (
                    self.left[node] if bit
                    else self.right[node]
                )

                if preferred != -1 and self.cnt[preferred] > 0:
                    result |= 1 << b
                    node = preferred
                else:
                    node = (
                        self.right[node] if bit
                        else self.left[node]
                    )

            return result

    visited = [False] * N

    for start in range(N):
        if removed[start] or visited[start]:
            continue

        cycle = []
        u = start

        while not visited[u]:
            visited[u] = True
            cycle.append(u)
            u = A[u]

        L = len(cycle)

        prefix = [0]
        for j in range(3 * L):
            prefix.append(
                prefix[-1] ^ V[cycle[j % L]]
            )

        cycle_trie = Trie()

        for j in range(1, 2 * L + 1):
            cycle_trie.add(prefix[j], 1)

        for i, root in enumerate(cycle):
            base = prefix[i]
            ans[root] = max(
                0, cycle_trie.query(base)
            )

            tree_trie = Trie()
            tree_trie.add(0, 1)

            stack = [(root, 0, 0)]

            while stack:
                node, x, stage = stack.pop()

                if stage == 1:
                    tree_trie.add(x, -1)
                    continue

                if node != root:
                    ans[node] = max(
                        0,
                        tree_trie.query(x),
                        cycle_trie.query(x ^ base)
                    )

                    tree_trie.add(x, 1)
                    stack.append((node, x, 1))

                for child in rev[node]:
                    if not removed[child]:
                        continue

                    nx = x ^ V[child]
                    stack.append((child, nx, 0))

            if i + 1 < L:
                cycle_trie.add(prefix[i + 1], -1)
                cycle_trie.add(prefix[i + 2 * L + 1], 1)

    return ans


def main():
    T = int(input())

    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))

        print(' '.join(map(str, solve(N, A, V))))


if __name__ == '__main__':
    main()
