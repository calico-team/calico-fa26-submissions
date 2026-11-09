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

    def apply_xor(self, node, value):
        if node == 0:
            return 0

        copied = self.clone(node)
        self.lazy[copied] ^= value
        return copied

    def push(self, node, bit):
        tag = self.lazy[node]

        if tag == 0 or bit < 0:
            return

        lower_mask = (1 << bit) - 1

        if (tag >> bit) & 1:
            self.left[node], self.right[node] = (
                self.right[node],
                self.left[node],
            )

        lower_tag = tag & lower_mask

        if lower_tag:
            self.left[node] = self.apply_xor(
                self.left[node],
                lower_tag,
            )
            self.right[node] = self.apply_xor(
                self.right[node],
                lower_tag,
            )

        self.lazy[node] = 0

    def insert(self, root, value, bit=29):
        if root == 0:
            root = self.clone(0)

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

    def maximum_xor(self, root, value):
        if root == 0:
            return 0

        answer = 0
        accumulated_lazy = 0

        for bit in range(29, -1, -1):
            accumulated_lazy ^= self.lazy[root]

            desired_bit = ((value >> bit) & 1) ^ 1
            stored_bit = desired_bit ^ ((accumulated_lazy >> bit) & 1)

            preferred = (
                self.right[root]
                if stored_bit
                else self.left[root]
            )

            fallback = (
                self.left[root]
                if stored_bit
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
        entry_cycle = [-1] * n

        for start in range(n):
            if not on_cycle[start] or entry_cycle[start] != -1:
                continue

            cycle = []
            node = start

            while True:
                cycle.append(node)
                entry_cycle[node] = start
                node = target[node]

                if node == start:
                    break

            length = len(cycle)
            prefix = [0]

            for node in cycle:
                prefix.append(prefix[-1] ^ values[node])

            cycle_xor = prefix[-1]
            base_root = 0

            for value in prefix[:-1]:
                base_root = trie.insert(base_root, value)

            if cycle_xor:
                for value in prefix[:-1]:
                    base_root = trie.insert(
                        base_root,
                        value ^ cycle_xor,
                    )

            for index, node in enumerate(cycle):
                roots[node] = trie.apply_xor(
                    base_root,
                    prefix[index],
                )

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

            entry_cycle[node] = entry_cycle[nxt]

        for node in range(n):
            output.append(
                str(trie.maximum_xor(roots[node], 0))
            )

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()