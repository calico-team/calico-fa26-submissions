
import sys
from collections import deque
from array import array

class Trie:
    def __init__(self):
        self.left = array('i', [-1])
        self.right = array('i', [-1])
        self.cnt = array('i', [0])

    def add(self, x, delta=1):
        node = 0
        self.cnt[node] += delta

        for b in range(29, -1, -1):
            if (x >> b) & 1:
                nxt = self.right[node]
                if nxt == -1:
                    nxt = len(self.cnt)
                    self.right[node] = nxt
                    self.left.append(-1)
                    self.right.append(-1)
                    self.cnt.append(0)
                node = nxt
            else:
                nxt = self.left[node]
                if nxt == -1:
                    nxt = len(self.cnt)
                    self.left[node] = nxt
                    self.left.append(-1)
                    self.right.append(-1)
                    self.cnt.append(0)
                node = nxt

            self.cnt[node] += delta

    def query(self, x):
        node = 0
        result = 0

        for b in range(29, -1, -1):
            bit = (x >> b) & 1

            if bit:
                nxt = self.left[node]
                same = self.right[node]
            else:
                nxt = self.right[node]
                same = self.left[node]

            if nxt != -1 and self.cnt[nxt] > 0:
                result |= (1 << b)
                node = nxt
            else:
                node = same

        return result


def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N = int(input())
        A = [x - 1 for x in map(int, input().split())]
        V = list(map(int, input().split()))

        rev = [[] for _ in range(N)]
        indeg = [0] * N

        for u in range(N):
            rev[A[u]].append(u)
            indeg[A[u]] += 1

        # Find all cycle nodes
        q = deque()

        for i in range(N):
            if indeg[i] == 0:
                q.append(i)

        while q:
            u = q.popleft()
            v = A[u]
            indeg[v] -= 1

            if indeg[v] == 0:
                q.append(v)

        is_cycle = [indeg[i] > 0 for i in range(N)]
        visited = [False] * N
        ans = [0] * N

        # Process each cycle
        for start in range(N):
            if not is_cycle[start] or visited[start]:
                continue

            cycle = []
            u = start

            while not visited[u]:
                visited[u] = True
                cycle.append(u)
                u = A[u]

            L = len(cycle)

            # Prefix XORs around the cycle
            P = [0] * (L + 1)

            for j in range(L):
                P[j + 1] = P[j] ^ V[cycle[j]]

            C = P[L]

            # Trie of cycle prefix XORs
            ct = Trie()

            for j in range(L):
                ct.add(P[j])

            # DFS through trees attached to this cycle
            for j in range(L):
                root = cycle[j]
                anc = Trie()

                # (node, prefix XOR, entering/exiting)
                stack = [(root, V[root], 1)]

                while stack:
                    u, pref, entering = stack.pop()

                    if entering:
                        # Best result using cycle positions
                        x = pref ^ P[j + 1]
                        best = ct.query(x)

                        if C:
                            best = max(best, ct.query(x ^ C))

                        # Best result stopping in the tree
                        if anc.cnt[0] > 0:
                            best = max(best, anc.query(pref))

                        ans[u] = best

                        anc.add(pref)

                        # Exit event
                        stack.append((u, pref, 0))

                        # Visit children
                        for v in rev[u]:
                            if not is_cycle[v]:
                                stack.append((v, pref ^ V[v], 1))

                    else:
                        anc.add(pref, -1)

        print(*ans)


if __name__ == "__main__":
    solve()
