
from array import array


class Trie:
    def __init__(self):
        self.zero = array('i', [0])
        self.one = array('i', [0])
        self.count = array('i', [0])
        self.free_head = 0
        self.path = [0] * 31

    def new_node(self):
        if self.free_head:
            node = self.free_head
            self.free_head = self.zero[node]
            self.zero[node] = 0
            self.one[node] = 0
            self.count[node] = 0
            return node

        node = len(self.count)
        self.zero.append(0)
        self.one.append(0)
        self.count.append(0)
        return node

    def add(self, x, delta):
        node = 0
        self.count[node] += delta
        self.path[0] = 0

        for depth, bit in enumerate(range(29, -1, -1), 1):
            if (x >> bit) & 1:
                nxt = self.one[node]
                if nxt == 0:
                    nxt = self.new_node()
                    self.one[node] = nxt
            else:
                nxt = self.zero[node]
                if nxt == 0:
                    nxt = self.new_node()
                    self.zero[node] = nxt

            node = nxt
            self.count[node] += delta
            self.path[depth] = node

        if delta < 0:
            for depth in range(30, 0, -1):
                node = self.path[depth]

                if self.count[node] != 0:
                    break

                parent = self.path[depth - 1]
                bit = 30 - depth

                if (x >> bit) & 1:
                    self.one[parent] = 0
                else:
                    self.zero[parent] = 0

                self.zero[node] = self.free_head
                self.one[node] = 0
                self.free_head = node

    def query(self, x):
        node = 0
        result = 0

        for bit in range(29, -1, -1):
            if (x >> bit) & 1:
                nxt = self.zero[node]
                if nxt != 0 and self.count[nxt] > 0:
                    result |= (1 << bit)
                else:
                    nxt = self.one[node]
            else:
                nxt = self.one[node]
                if nxt != 0 and self.count[nxt] > 0:
                    result |= (1 << bit)
                else:
                    nxt = self.zero[node]

            node = nxt

        return result


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    # YOUR CODE HERE

    A = [x - 1 for x in A]

    rev = [[] for _ in range(N)]
    indeg = [0] * N

    for i in range(N):
        rev[A[i]].append(i)
        indeg[A[i]] += 1

    # Remove nodes that are not part of cycles.
    from collections import deque

    q = deque(i for i in range(N) if indeg[i] == 0)

    while q:
        u = q.popleft()
        v = A[u]
        indeg[v] -= 1

        if indeg[v] == 0:
            q.append(v)

    in_cycle = [indeg[i] > 0 for i in range(N)]

    answer = [0] * N
    prefix = [0] * N
    trie = Trie()

    visited = [False] * N

    # Process each directed cycle.
    for start in range(N):
        if not in_cycle[start] or visited[start]:
            continue

        cycle = []
        u = start

        while not visited[u]:
            visited[u] = True
            cycle.append(u)
            u = A[u]

        L = len(cycle)

        # Build the reverse tree belonging to each cycle node.
        for root in cycle:
            prefix[root] = V[root]

            nodes = []
            stack = [root]

            while stack:
                u = stack.pop()
                nodes.append(u)

                for w in rev[u]:
                    if not in_cycle[w]:
                        prefix[w] = prefix[u] ^ V[w]
                        stack.append(w)

            # Find the best XOR among prefixes on the path
            # from each node to its cycle root.
            trie.add(0, 1)

            stack = [(root, False)]

            while stack:
                u, exiting = stack.pop()

                if not exiting:
                    answer[u] = max(
                        answer[u],
                        trie.query(prefix[u])
                    )

                    trie.add(prefix[u], 1)
                    stack.append((u, True))

                    for w in rev[u]:
                        if not in_cycle[w]:
                            stack.append((w, False))
                else:
                    trie.add(prefix[u], -1)

            trie.add(0, -1)

            # Find the best XOR obtainable by continuing
            # around the cycle.
            #
            # Repeat the cycle three times to build prefix XORs.
            cycle_prefix = [0] * (3 * L + 1)

            for j in range(3 * L):
                cycle_prefix[j + 1] = (
                    cycle_prefix[j] ^ V[cycle[j % L]]
                )

            # Initially maintain cycle prefix values
            # from index 2 through index 2L.
            for j in range(2, 2 * L + 1):
                trie.add(cycle_prefix[j], 1)

            # Slide the range for each possible cycle starting node.
            for i in range(L):
                base = cycle_prefix[i + 1]

                for u in nodes:
                    candidate = trie.query(prefix[u] ^ base)
                    answer[u] = max(answer[u], candidate)

                if i + 1 < L:
                    trie.add(cycle_prefix[i + 2], -1)
                    trie.add(cycle_prefix[i + 2 * L + 1], 1)

            # Remove the remaining cycle prefix values.
            for j in range(L + 1, 3 * L):
                trie.add(cycle_prefix[j], -1)

    return answer


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))


if __name__ == '__main__':
    main()
