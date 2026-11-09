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

import sys
from array import array
from collections import deque


class BinaryTrie:
    def __init__(self):
        self.left = array('i', [0])
        self.right = array('i', [0])

    def new_node(self):
        self.left.append(0)
        self.right.append(0)
        return len(self.left) - 1

    def insert_base(self, root, x):
        node = root

        for bit in range(29, -1, -1):
            if (x >> bit) & 1:
                nxt = self.right[node]
                if nxt == 0:
                    nxt = self.new_node()
                    self.right[node] = nxt
            else:
                nxt = self.left[node]
                if nxt == 0:
                    nxt = self.new_node()
                    self.left[node] = nxt

            node = nxt

    def insert_persistent(self, root, x):
        new_root = self.new_node()

        self.left[new_root] = self.left[root]
        self.right[new_root] = self.right[root]

        old_node = root
        new_node = new_root

        for bit in range(29, -1, -1):
            if (x >> bit) & 1:
                old_child = self.right[old_node]
                new_child = self.new_node()

                if old_child:
                    self.left[new_child] = self.left[old_child]
                    self.right[new_child] = self.right[old_child]

                self.right[new_node] = new_child
            else:
                old_child = self.left[old_node]
                new_child = self.new_node()

                if old_child:
                    self.left[new_child] = self.left[old_child]
                    self.right[new_child] = self.right[old_child]

                self.left[new_node] = new_child

            old_node = old_child
            new_node = new_child

        return new_root

    def max_xor(self, root, x):
        node = root
        result = 0

        for bit in range(29, -1, -1):
            current_bit = (x >> bit) & 1

            if current_bit == 0:
                preferred = self.right[node]
                alternative = self.left[node]
            else:
                preferred = self.left[node]
                alternative = self.right[node]

            if preferred:
                result |= (1 << bit)
                node = preferred
            else:
                node = alternative

        return result


def solve(N, A, V):
    A = [x - 1 for x in A]

    trie = BinaryTrie()
    indegree = [0] * N

    for u in range(N):
        indegree[A[u]] += 1

    queue = deque()

    for u in range(N):
        if indegree[u] == 0:
            queue.append(u)

    removed = []

    while queue:
        u = queue.popleft()
        removed.append(u)

        p = A[u]
        indegree[p] -= 1

        if indegree[p] == 0:
            queue.append(p)

    visited = [False] * N

    pot = [0] * N
    version = [0] * N
    answer = [0] * N

    # Process cycles.
    for start in range(N):
        if indegree[start] == 0 or visited[start]:
            continue

        cycle = []
        u = start

        while not visited[u]:
            visited[u] = True
            cycle.append(u)
            u = A[u]

        prefix = 0
        cycle_prefixes = []

        for u in cycle:
            pot[u] = prefix
            prefix ^= V[u]
            cycle_prefixes.append(prefix)

        cycle_xor = prefix
        root = trie.new_node()

        for x in cycle_prefixes:
            trie.insert_base(root, x)

        if cycle_xor != 0:
            for x in cycle_prefixes:
                trie.insert_base(root, x ^ cycle_xor)

        for u in cycle:
            version[u] = root
            answer[u] = trie.max_xor(root, pot[u])

    # Process tree nodes.
    for u in reversed(removed):
        p = A[u]

        pot[u] = V[u] ^ pot[p]
        version[u] = trie.insert_persistent(version[p], pot[p])

        answer[u] = trie.max_xor(version[u], pot[u])

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
