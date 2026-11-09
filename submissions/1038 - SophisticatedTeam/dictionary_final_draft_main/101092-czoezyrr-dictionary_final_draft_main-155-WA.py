import sys


def read_your_input():
    return sys.stdin.buffer.read().split()


class PersistentTrie:
    def __init__(self):
        self.left = [0]
        self.right = [0]
        self.lazy = [0]

    def clone(self, node):
        self.left.append(self.left[node])
        self.right.append(self.right[node])
        self.lazy.append(self.lazy[node])
        return len(self.left) - 1

    def apply_xor(self, root, value):
        if root == 0:
            return 0

        node = self.clone(root)
        self.lazy[node] ^= value
        return node

    def push(self, node):
        value = self.lazy[node]

        if value == 0:
            return

        self.left[node] = self.apply_xor(
            self.left[node],
            value,
        )
        self.right[node] = self.apply_xor(
            self.right[node],
            value,
        )
        self.lazy[node] = 0

    def insert(self, root, value, bit=29):
        if root == 0:
            root = self.clone(0)
        else:
            root = self.clone(root)

        if bit < 0:
            return root

        self.push(root)

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
        if root == 0:
            return 0

        answer = 0
        accumulated_xor = 0

        for bit in range(29, -1, -1):
            accumulated_xor ^= self.lazy[root]

            desired = ((value >> bit) & 1) ^ 1
            raw_desired = desired ^ ((accumulated_xor >> bit) & 1)

            if raw_desired:
                preferred = self.right[root]
                fallback = self.left[root]
            else:
                preferred = self.left[root]
                fallback = self.right[root]

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

        values = [
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

        trie = PersistentTrie()
        roots = [0] * n
        seen_cycle = [False] * n

        # Build the set of possible XOR values for every cycle node.
        for start in range(n):
            if not on_cycle[start] or seen_cycle[start]:
                continue

            cycle = []
            node = start

            while not seen_cycle[node]:
                seen_cycle[node] = True
                cycle.append(node)
                node = target[node]

            prefix = [0]

            for node in cycle:
                prefix.append(prefix[-1] ^ values[node])

            cycle_xor = prefix[-1]
            base_root = 0

            for value in prefix[1:]:
                base_root = trie.insert(base_root, value)

            if cycle_xor != 0:
                for value in prefix[1:]:
                    base_root = trie.insert(
                        base_root,
                        value ^ cycle_xor,
                    )

            current_prefix = 0

            for node in cycle:
                roots[node] = trie.apply_xor(
                    base_root,
                    current_prefix,
                )
                current_prefix ^= values[node]

        # Build answers for nodes outside cycles.
        for node in reversed(queue):
            nxt = target[node]

            shifted_root = trie.apply_xor(
                roots[nxt],
                values[node],
            )

            roots[node] = trie.insert(
                shifted_root,
                values[node],
            )

        for node in range(n):
            output.append(
                str(trie.maximum_xor(roots[node], 0))
            )

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()