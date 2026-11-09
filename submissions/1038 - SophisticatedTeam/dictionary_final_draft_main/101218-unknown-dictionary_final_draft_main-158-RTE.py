import sys
from array import array


def read_your_input():
    return sys.stdin.buffer.read().split()


class PersistentTrie:
    def __init__(self):
        self.left = array("i", [0])
        self.right = array("i", [0])
        self.lazy = array("i", [0])

    def clone(self, node):
        self.left.append(self.left[node])
        self.right.append(self.right[node])
        self.lazy.append(self.lazy[node])
        return len(self.left) - 1

    def apply_xor(self, node, value, bit=29):
        if node == 0:
            return 0

        new_node = self.clone(node)
        mask = (1 << (bit + 1)) - 1

        if (value >> bit) & 1:
            self.left[new_node], self.right[new_node] = (
                self.right[new_node],
                self.left[new_node],
            )

        self.lazy[new_node] ^= value & mask
        return new_node

    def push(self, node, bit):
        tag = self.lazy[node]

        if tag == 0 or bit < 0:
            return

        self.left[node] = self.apply_xor(
            self.left[node],
            tag,
            bit - 1,
        )

        self.right[node] = self.apply_xor(
            self.right[node],
            tag,
            bit - 1,
        )

        self.lazy[node] = 0

    def insert(self, root, value, bit=29):
        if root == 0:
            root = self.clone(0)
        else:
            root = self.clone(root)

        if bit < 0:
            return root

        self.push(root, bit)

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

    def maximum_xor(self, root, value, bit=29, inherited=0):
        if root == 0 or bit < 0:
            return 0

        inherited ^= self.lazy[root]

        wanted = ((value >> bit) & 1) ^ 1
        raw_wanted = wanted ^ ((inherited >> bit) & 1)

        if raw_wanted:
            preferred = self.right[root]
            fallback = self.left[root]
        else:
            preferred = self.left[root]
            fallback = self.right[root]

        if preferred:
            return (
                (1 << bit)
                | self.maximum_xor(
                    preferred,
                    value,
                    bit - 1,
                    inherited,
                )
            )

        return self.maximum_xor(
            fallback,
            value,
            bit - 1,
            inherited,
        )


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
        cycle_seen = [False] * n

        # Build the set of possible values for cycle nodes.
        for start in range(n):
            if not on_cycle[start] or cycle_seen[start]:
                continue

            cycle = []
            node = start

            while not cycle_seen[node]:
                cycle_seen[node] = True
                cycle.append(node)
                node = target[node]

            length = len(cycle)
            prefix = [0]

            for node in cycle:
                prefix.append(prefix[-1] ^ values[node])

            cycle_xor = prefix[length]
            base_root = 0

            # P[0], P[1], ..., P[length - 1]
            for i in range(length):
                base_root = trie.insert(
                    base_root,
                    prefix[i],
                )

            # If the cycle XOR is nonzero, another lap gives XOR + cycle_xor.
            if cycle_xor != 0:
                for i in range(length):
                    base_root = trie.insert(
                        base_root,
                        prefix[i] ^ cycle_xor,
                    )

            current_prefix = 0

            for node in cycle:
                roots[node] = trie.apply_xor(
                    base_root,
                    current_prefix,
                )
                current_prefix ^= values[node]

        # Process all non-cycle nodes from the leaves toward the cycles.
        for node in reversed(queue):
            nxt = target[node]

            shifted = trie.apply_xor(
                roots[nxt],
                values[node],
            )

            roots[node] = trie.insert(
                shifted,
                values[node],
            )

        for node in range(n):
            answer = trie.maximum_xor(roots[node], 0)
            output.append(str(answer))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()