import sys


def read_your_input():
    return sys.stdin.buffer.read().split()


class BinaryTrie:
    def __init__(self):
        self.left = [0]
        self.right = [0]

    def add(self, value):
        node = 0

        for bit in range(29, -1, -1):
            if (value >> bit) & 1:
                if self.right[node] == 0:
                    self.right[node] = len(self.left)
                    self.left.append(0)
                    self.right.append(0)
                node = self.right[node]
            else:
                if self.left[node] == 0:
                    self.left[node] = len(self.left)
                    self.left.append(0)
                    self.right.append(0)
                node = self.left[node]

    def maximum_xor(self, value):
        node = 0
        result = 0

        for bit in range(29, -1, -1):
            wanted = (value >> bit) & 1
            preferred = self.right[node] if wanted == 0 else self.left[node]
            fallback = self.left[node] if wanted == 0 else self.right[node]

            if preferred:
                result |= 1 << bit
                node = preferred
            else:
                node = fallback

        return result


class PersistentTrie:
    def __init__(self):
        self.left = [0]
        self.right = [0]

    def add(self, root, value):
        new_root = len(self.left)
        self.left.append(self.left[root])
        self.right.append(self.right[root])

        old = root
        current = new_root

        for bit in range(29, -1, -1):
            if (value >> bit) & 1:
                child = self.right[old]
                copied = len(self.left)
                self.left.append(self.left[child])
                self.right.append(self.right[child])
                self.right[current] = copied
            else:
                child = self.left[old]
                copied = len(self.left)
                self.left.append(self.left[child])
                self.right.append(self.right[child])
                self.left[current] = copied

            old = child
            current = copied

        return new_root

    def maximum_xor(self, root, value):
        node = root
        result = 0

        for bit in range(29, -1, -1):
            wanted = (value >> bit) & 1
            preferred = self.right[node] if wanted == 0 else self.left[node]
            fallback = self.left[node] if wanted == 0 else self.right[node]

            if preferred:
                result |= 1 << bit
                node = preferred
            else:
                node = fallback

        return result


def solve():
    data = iter(read_your_input())
    test_cases = int(next(data))
    output = []

    for _ in range(test_cases):
        n = int(next(data))
        target = [int(next(data)) - 1 for _ in range(n)]
        values = [int(next(data)) for _ in range(n)]

        indegree = [0] * n
        for node in range(n):
            indegree[target[node]] += 1

        queue = [node for node in range(n) if indegree[node] == 0]

        for node in queue:
            nxt = target[node]
            indegree[nxt] -= 1
            if indegree[nxt] == 0:
                queue.append(nxt)

        on_cycle = [degree > 0 for degree in indegree]
        entry = [-1] * n
        path_xor = [0] * n
        path_root = [0] * n
        cycle_tries = {}
        cycle_shifts = [0] * n
        persistent = PersistentTrie()

        for first in range(n):
            if not on_cycle[first] or entry[first] != -1:
                continue

            cycle = []
            node = first

            while True:
                cycle.append(node)
                node = target[node]
                if node == first:
                    break

            prefix = [0]

            for node in cycle:
                prefix.append(prefix[-1] ^ values[node])

            total_xor = prefix[-1]
            trie = BinaryTrie()

            for xor_value in prefix[:-1]:
                trie.add(xor_value)

                if total_xor:
                    trie.add(xor_value ^ total_xor)

            for index, node in enumerate(cycle):
                entry[node] = node
                cycle_shifts[node] = prefix[index]
                cycle_tries[node] = trie
                path_root[node] = persistent.add(0, 0)

        for node in reversed(queue):
            nxt = target[node]
            entry[node] = entry[nxt]
            path_xor[node] = values[node] ^ path_xor[nxt]
            path_root[node] = persistent.add(
                path_root[nxt],
                path_xor[nxt],
            )

        for node in range(n):
            if on_cycle[node]:
                answer = cycle_tries[node].maximum_xor(cycle_shifts[node])
            else:
                tail_answer = persistent.maximum_xor(
                    path_root[node],
                    path_xor[node],
                )

                cycle_answer = cycle_tries[entry[node]].maximum_xor(
                    path_xor[node],
                )

                answer = max(tail_answer, cycle_answer)

            output.append(str(answer))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()