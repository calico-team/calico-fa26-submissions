from collections import deque
from array import array
    
def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
 

    A = [x - 1 for x in A]

    rev = [[] for _ in range(N)]
    indegree = [0] * N

    for i in range(N):
        rev[A[i]].append(i)
        indegree[A[i]] += 1

    queue = deque(i for i in range(N) if indegree[i] == 0)
    removed = bytearray(N)

    while queue:
        u = queue.popleft()
        removed[u] = 1
        v = A[u]
        indegree[v] -= 1

        if indegree[v] == 0:
            queue.append(v)

    class Trie:
        def __init__(self):
            self.zero = array('i', [-1])
            self.one = array('i', [-1])
            self.count = array('i', [0])

        def add(self, x, delta=1):
            node = 0
            self.count[node] += delta

            for bit in range(29, -1, -1):
                b = (x >> bit) & 1

                if b == 0:
                    nxt = self.zero[node]
                    if nxt == -1:
                        nxt = len(self.count)
                        self.zero[node] = nxt
                        self.zero.append(-1)
                        self.one.append(-1)
                        self.count.append(0)
                else:
                    nxt = self.one[node]
                    if nxt == -1:
                        nxt = len(self.count)
                        self.one[node] = nxt
                        self.zero.append(-1)
                        self.one.append(-1)
                        self.count.append(0)

                node = nxt
                self.count[node] += delta

        def query(self, x):
            node = 0
            result = 0

            for bit in range(29, -1, -1):
                b = (x >> bit) & 1

                if b == 0:
                    preferred = self.one[node]
                    alternative = self.zero[node]
                else:
                    preferred = self.zero[node]
                    alternative = self.one[node]

                if preferred != -1 and self.count[preferred] > 0:
                    result |= (1 << bit)
                    node = preferred
                else:
                    node = alternative

            return result

    ans = [0] * N
    visited = bytearray(N)

    for start in range(N):
        if removed[start] or visited[start]:
            continue

        cycle = []
        u = start

        while not visited[u]:
            visited[u] = 1
            cycle.append(u)
            u = A[u]

        prefixes = []
        total_xor = 0

        for u in cycle:
            total_xor ^= V[u]
            prefixes.append(total_xor)

        cycle_trie = Trie()

        for x in prefixes:
            cycle_trie.add(x)

        if total_xor != 0:
            for x in prefixes:
                cycle_trie.add(x ^ total_xor)

        prefix_before = 0

        for root in cycle:
            ans[root] = cycle_trie.query(prefix_before)

            path_trie = Trie()
            path_trie.add(0)

            stack = []

            for child in rev[root]:
                if removed[child]:
                    stack.append((child, V[child], 0))

            while stack:
                u, p, state = stack.pop()

                if state == 0:
                    tree_best = path_trie.query(p)
                    cycle_best = cycle_trie.query(p ^ prefix_before)

                    ans[u] = max(tree_best, cycle_best)

                    path_trie.add(p)
                    stack.append((u, p, 1))

                    for child in rev[u]:
                        if removed[child]:
                            stack.append((child, p ^ V[child], 0))

                else:
                    path_trie.add(p, -1)

            prefix_before ^= V[root]

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
