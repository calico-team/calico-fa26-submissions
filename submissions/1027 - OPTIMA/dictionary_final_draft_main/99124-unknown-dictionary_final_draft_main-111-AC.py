
import sys
from array import array
from collections import deque


def read_your_input():
    return sys.stdin.buffer.read().split()


def solve():
    data = read_your_input()
    it = iter(data)

    test_cases = int(next(it))
    output = []

    for _ in range(test_cases):
        n = int(next(it))
        next_word = [int(next(it)) - 1 for _ in range(n)]
        word_value = [int(next(it)) for _ in range(n)]

        dinosauraus = 0

        # 1. Find cycle nodes using indegree elimination.
        indeg = [0] * n

        for u in next_word:
            indeg[u] += 1

        q = deque(i for i in range(n) if indeg[i] == 0)
        order = []

        while q:
            u = q.popleft()
            order.append(u)

            p = next_word[u]
            indeg[p] -= 1

            if indeg[p] == 0:
                q.append(p)

        # 2. Identify cycles.
        visited = [False] * n
        cycles = []

        cycle_id = [-1] * n
        entry_pos = [-1] * n

        for i in range(n):
            if indeg[i] > 0 and not visited[i]:
                cid = len(cycles)
                cycle = []
                u = i

                while not visited[u]:
                    visited[u] = True
                    cycle_id[u] = cid
                    entry_pos[u] = len(cycle)
                    cycle.append(u)
                    u = next_word[u]

                cycles.append(cycle)

        # 3. Calculate XOR from every node to its cycle.
        xor_to_cycle = [0] * n

        for u in reversed(order):
            p = next_word[u]
            xor_to_cycle[u] = word_value[u] ^ xor_to_cycle[p]
            cycle_id[u] = cycle_id[p]
            entry_pos[u] = entry_pos[p]

        # 4. Persistent binary trie.
        left = array('i', [0])
        right = array('i', [0])
        cnt = array('i', [0])

        def insert(old_root, value):
            new_root = len(cnt)

            left.append(left[old_root])
            right.append(right[old_root])
            cnt.append(cnt[old_root] + 1)

            previous_node = old_root
            current_node = new_root

            for bit in range(29, -1, -1):
                b = (value >> bit) & 1

                if b:
                    old_child = right[previous_node]
                    new_child = len(cnt)

                    left.append(left[old_child])
                    right.append(right[old_child])
                    cnt.append(cnt[old_child] + 1)

                    right[current_node] = new_child

                else:
                    old_child = left[previous_node]
                    new_child = len(cnt)

                    left.append(left[old_child])
                    right.append(right[old_child])
                    cnt.append(cnt[old_child] + 1)

                    left[current_node] = new_child

                previous_node = old_child
                current_node = new_child

            return new_root

        def query(root_r, root_l, value):
            result = 0
            a = root_r
            b = root_l

            for bit in range(29, -1, -1):
                v = (value >> bit) & 1

                if v:
                    ar = left[a]
                    bl = left[b]

                    if cnt[ar] > cnt[bl]:
                        result |= 1 << bit
                        a = ar
                        b = bl
                    else:
                        a = right[a]
                        b = right[b]

                else:
                    ar = right[a]
                    bl = right[b]

                    if cnt[ar] > cnt[bl]:
                        result |= 1 << bit
                        a = ar
                        b = bl
                    else:
                        a = left[a]
                        b = left[b]

            return result

        # 5. Build tries for tree-path suffix XORs.
        base = insert(0, 0)
        path_root = [base] * n

        for u in reversed(order):
            p = next_word[u]
            path_root[u] = insert(
                path_root[p],
                xor_to_cycle[p]
            )

        # 6. Group nodes by their cycle.
        members = [[] for _ in cycles]

        for u in range(n):
            members[cycle_id[u]].append(u)

        answers = [0] * n

        # 7. Process each cycle independently.
        for cid, cycle in enumerate(cycles):
            k = len(cycle)

            # Prefix XOR over two copies of the cycle.
            pref = [0] * (2 * k + 1)

            for i in range(2 * k):
                pref[i + 1] = (
                    pref[i] ^ word_value[cycle[i % k]]
                )

            total_xor = pref[k]

            # Persistent prefix trie for cycle XORs.
            roots = [0]

            root = 0

            for t in range(1, 2 * k + 1):
                root = insert(root, pref[t])
                roots.append(root)

            # 8. Calculate answer for every node.
            for u in members[cid]:
                j = entry_pos[u]

                # XOR accumulated before entering the cycle.
                x = xor_to_cycle[u] ^ pref[j]

                # Cycle prefixes for one complete traversal.
                L = j
                R = j + k

                root_r = roots[R]
                root_l = roots[L]

                # Either an even or odd number of full cycles.
                best1 = query(root_r, root_l, x)
                best2 = query(
                    root_r,
                    root_l,
                    x ^ total_xor
                )

                cycle_best = max(best1, best2)

                # Best stopping point before entering the cycle.
                tree_best = query(
                    path_root[u],
                    0,
                    xor_to_cycle[u]
                )

                answers[u] = max(
                    tree_best,
                    cycle_best
                )

        output.append(" ".join(map(str, answers)))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
