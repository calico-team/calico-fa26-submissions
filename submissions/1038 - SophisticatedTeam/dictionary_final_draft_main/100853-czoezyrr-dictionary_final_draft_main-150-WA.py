import sys


def read_your_input():
    return sys.stdin.buffer.read().split()


class PersistentXorTrie:
    def __init__(self):
        self.left = [0]
        self.right = [0]
        self.lazy = [0]

    def new_node(self, left=0, right=0, lazy=0):
        self.left.append(left)
        self.right.append(right)
        self.lazy.append(lazy)
        return len(self.left) - 1

    def apply_xor(self, node, value):
        if node == 0:
            return 0

        return self.new_node(
            self.left[node],
            self.right[node],
            self.lazy[node] ^ value,
        )

    def push(self, node):
        tag = self.lazy[node]

        if tag == 0:
            return

        self.left[node] = self.apply_xor(self.left[node], tag)
        self.right[node] = self.apply_xor(self.right[node], tag)
        self.lazy[node] = 0

    def insert(self, root, value, bit=29):
        if root == 0:
            root = self.new_node()

        root = self.new_node(
            self.left[root],
            self.right[root],
            self.lazy[root],
        )
        self.push(root)

        if bit < 0:
            return root

        if (value >> bit) & 1:
            self.right[root] = self.insert(
                self.right[root],
                value,
                bit - 1,
            )
        else:
            self.left[root] = self.insert(
                self.left[root],
                value,
                bit - 1,
            )

        return root

    def maximum_xor(self, root, value):
        answer = 0

        for bit in range(29, -1, -1):
            tag_bit = (self.lazy[root] >> bit) & 1
            wanted = ((value >> bit) & 1) ^ 1
            stored_branch = wanted ^ tag_bit

            preferred = (
                self.right[root]
                if stored_branch
                else self.left[root]
            )

            fallback = (
                self.left[root]
                if stored_branch
                else self.right[root]
            )

            if preferred:
                answer |= 1 << bit
                root = preferred
            else:
                root = fallback

        return answer


def solve():
    data = iter(read_your_input())
    test_cases = int(next(data))
    output = []

    for _ in range(test_cases):
        n = int(next(data))

        target = [
            int(next(data)) - 1
            for _ in range(n)
        ]

        value = [
            int(next(data))
            for _ in range(n)
        ]

        indegree = [0] * n

        for node in range(n):
            indegree[target[node]] += 1

        queue = [
            node
            for node in range(n)
            if indegree[node] == 0
        ]

        for node in queue:
            nxt = target[node]
            indegree[nxt] -= 1

            if indegree[nxt] == 0:
                queue.append(nxt)

        on_cycle = [
            indegree[node] > 0
            for node in range(n)
        ]

        trie = PersistentXorTrie()
        roots = [0] * n

        # Build a trie for every cycle.
        visited_cycle = [False] * n

        for start in range(n):
            if not on_cycle[start] or visited_cycle[start]:
                continue

            cycle = []
            node = start

            while not visited_cycle[node]:
                visited_cycle[node] = True
                cycle.append(node)
                node = target[node]

            prefix = 0
            prefixes = []

            for node in cycle:
                prefix ^= value[node]
                prefixes.append(prefix)

            cycle_xor = prefix
            root = 0

            for prefix in prefixes:
                root = trie.insert(root, prefix)

            if cycle_xor != 0:
                for prefix in prefixes:
                    root = trie.insert(
                        root,
                        prefix ^ cycle_xor,
                    )

            for node in cycle:
                roots[node] = root

        # Process all non-cycle nodes backwards.
        for node in reversed(queue):
            nxt = target[node]

            shifted_root = trie.apply_xor(
                roots[nxt],
                value[node],
            )

            roots[node] = trie.insert(
                shifted_root,
                value[node],
            )

        for node in range(n):
            output.append(
                str(trie.maximum_xor(roots[node], 0))
            )

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()