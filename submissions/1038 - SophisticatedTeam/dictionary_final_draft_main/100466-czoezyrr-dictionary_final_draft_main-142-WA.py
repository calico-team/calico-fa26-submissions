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
                child = self.right[node]
                if child == 0:
                    child = len(self.left)
                    self.left.append(0)
                    self.right.append(0)
                    self.right[node] = child
            else:
                child = self.left[node]
                if child == 0:
                    child = len(self.left)
                    self.left.append(0)
                    self.right.append(0)
                    self.left[node] = child
            node = child

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
        result = 0
        node = root
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
        value = [int(next(data)) for _ in range(n)]

        indegree = [0] * n
        reverse = [[] for _ in range(n)]
        for node, nxt in enumerate(target):
            indegree[nxt] += 1
            reverse[nxt].append(node)

        queue = [node for node in range(n) if indegree[node] == 0]
        for node in queue:
            nxt = target[node]
            indegree[nxt] -= 1
            if indegree[nxt] == 0:
                queue.append(nxt)

        on_cycle = [degree > 0 for degree in indegree]
        entry = [-1] * n
        depth = [0] * n
        path_xor = [0] * n
        path_root = [0] * n
        cycle_trie = {}
        cycle_shift = [0] * n
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
                prefix.append(prefix[-1] ^ value[node])

            total = prefix[-1]
            trie = BinaryTrie()
            for x in prefix[:-1]:
                trie.add(x)
                if total:
                    trie.add(x ^ total)

            for offset, node in enumerate(cycle):
                entry[node] = node
                cycle_shift[node] = prefix[offset]
                cycle_trie[node] = trie

        for node in range(n):
            if on_cycle[node]:
                path_root[node] = persistent.add(0, 0)

        order = list(reversed(queue))
        for node in order:
            nxt = target[node]
            entry[node] = entry[nxt]
            depth[node] = depth[nxt] + 1
            path_xor[node] = value[node] ^ path_xor[nxt]
            parent = target[node]
            path_root[node] = persistent.add(path_root[parent], path_xor[parent])

        for node in range(n):
            if on_cycle[node]:
                shift = cycle_shift[node]
                answer = cycle_trie[node].maximum_xor(shift)
            else:
                current_xor = path_xor[node]
                tail_answer = persistent.maximum_xor(path_root[node], current_xor)
                cycle_answer = cycle_trie[entry[node]].maximum_xor(current_xor)
                answer = max(tail_answer, cycle_answer)
            output.append(str(answer))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
