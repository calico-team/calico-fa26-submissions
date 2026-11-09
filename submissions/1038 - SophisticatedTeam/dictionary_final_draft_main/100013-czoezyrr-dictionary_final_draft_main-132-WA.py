import sys
from array import array


def read_your_input():
    return sys.stdin.buffer.read().split()


def solve():
    data = iter(read_your_input())
    test_cases = int(next(data))
    output = []

    for _ in range(test_cases):
        n = int(next(data))
        to = [int(next(data)) - 1 for _ in range(n)]
        value = [int(next(data)) for _ in range(n)]

        indegree = [0] * n
        reverse = [[] for _ in range(n)]
        for node, target in enumerate(to):
            indegree[target] += 1
            reverse[target].append(node)

        queue = [node for node in range(n) if indegree[node] == 0]
        peeled = []
        for node in queue:
            peeled.append(node)
            target = to[node]
            indegree[target] -= 1
            if indegree[target] == 0:
                queue.append(target)

        cycle_nodes = [node for node in range(n) if indegree[node]]
        is_cycle = [bool(x) for x in indegree]
        entry = [-1] * n
        cycle_offset = [0] * n
        cycle_shift = [0] * n
        cycle_trie = [0] * n
        xor_to_entry = [0] * n

        left = array("i", [0])
        right = array("i", [0])

        def insert(root, number):
            new_root = len(left)
            left.append(left[root])
            right.append(right[root])
            old = root
            current = new_root
            for bit in range(29, -1, -1):
                if (number >> bit) & 1:
                    old_child = right[old]
                    child = len(left)
                    left.append(left[old_child])
                    right.append(right[old_child])
                    right[current] = child
                else:
                    old_child = left[old]
                    child = len(left)
                    left.append(left[old_child])
                    right.append(right[old_child])
                    left[current] = child
                old = old_child
                current = child
            return new_root

        def best(root, number):
            answer = 0
            node = root
            for bit in range(29, -1, -1):
                wanted = (number >> bit) & 1
                preferred = right[node] if wanted == 0 else left[node]
                if preferred:
                    answer |= 1 << bit
                    node = preferred
                else:
                    node = left[node] if wanted == 0 else right[node]
            return answer

        for start in cycle_nodes:
            if entry[start] != -1:
                continue
            cycle = []
            node = start
            while True:
                entry[node] = start
                cycle_offset[node] = len(cycle)
                cycle.append(node)
                node = to[node]
                if node == start:
                    break

            prefix = [0]
            for node in cycle:
                prefix.append(prefix[-1] ^ value[node])
            total_xor = prefix[-1]
            root = 0
            for x in prefix[1:]:
                root = insert(root, x)
            if total_xor:
                for x in prefix[1:]:
                    root = insert(root, x ^ total_xor)
            for node in cycle:
                cycle_trie[node] = root
                cycle_shift[node] = prefix[cycle_offset[node]]

        for node in reversed(peeled):
            target = to[node]
            entry[node] = entry[target]
            xor_to_entry[node] = value[node] ^ xor_to_entry[target]

        roots = [0] * n
        for node in cycle_nodes:
            roots[node] = insert(0, 0)
        for node in reversed(peeled):
            target = to[node]
            roots[node] = insert(roots[target], xor_to_entry[target])

        for node in range(n):
            if is_cycle[node]:
                answer = best(cycle_trie[node], cycle_shift[node])
            else:
                target = to[node]
                answer = best(roots[target], xor_to_entry[node])
                answer = max(
                    answer,
                    best(
                        cycle_trie[entry[node]],
                        xor_to_entry[node] ^ cycle_shift[entry[node]],
                    ),
                )
            output.append(str(answer))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
