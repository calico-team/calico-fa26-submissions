import sys
from array import array


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    it = iter(data)
    T = int(next(it))
    out_lines = []

    for _ in range(T):
        N = int(next(it))

        A = [0] * (N + 1)
        for i in range(1, N + 1):
            A[i] = int(next(it))

        V = [0] * (N + 1)
        for i in range(1, N + 1):
            V[i] = int(next(it))

        children = [[] for _ in range(N + 1)]
        indegree = [0] * (N + 1)

        for i in range(1, N + 1):
            p = A[i]
            children[p].append(i)
            indegree[p] += 1

        # Peel off all non-cycle nodes.
        queue = [i for i in range(1, N + 1) if indegree[i] == 0]
        head = 0
        while head < len(queue):
            u = queue[head]
            head += 1
            v = A[u]
            indegree[v] -= 1
            if indegree[v] == 0:
                queue.append(v)

        is_cycle = [False] * (N + 1)
        for i in range(1, N + 1):
            if indegree[i] > 0:
                is_cycle[i] = True

        ans = [0] * (N + 1)
        D = [0] * (N + 1)
        visited_cycle = [False] * (N + 1)

        # Persistent trie for tree paths.
        left = array('i', [0])
        right = array('i', [0])

        def insert_persistent(old_root, val):
            new_root = len(left)
            left.append(left[old_root] if old_root else 0)
            right.append(right[old_root] if old_root else 0)

            cur_new = new_root
            cur_old = old_root

            for bit in range(29, -1, -1):
                b = (val >> bit) & 1
                if b == 0:
                    old_child = left[cur_old] if cur_old else 0
                    new_child = len(left)
                    left.append(left[old_child] if old_child else 0)
                    right.append(right[old_child] if old_child else 0)
                    left[cur_new] = new_child
                else:
                    old_child = right[cur_old] if cur_old else 0
                    new_child = len(left)
                    left.append(left[old_child] if old_child else 0)
                    right.append(right[old_child] if old_child else 0)
                    right[cur_new] = new_child

                cur_new = new_child
                cur_old = old_child

            return new_root

        def query_persistent(root, key):
            res = 0
            cur = root
            for bit in range(29, -1, -1):
                if cur == 0:
                    break
                b = (key >> bit) & 1
                if b == 0:
                    if right[cur]:
                        res |= (1 << bit)
                        cur = right[cur]
                    else:
                        cur = left[cur]
                else:
                    if left[cur]:
                        res |= (1 << bit)
                        cur = left[cur]
                    else:
                        cur = right[cur]
            return res

        def insert_cycle(ch0, ch1, root, val):
            if root == 0:
                root = len(ch0)
                ch0.append(0)
                ch1.append(0)

            cur = root
            for bit in range(29, -1, -1):
                b = (val >> bit) & 1
                if b == 0:
                    nxt = ch0[cur]
                    if nxt == 0:
                        nxt = len(ch0)
                        ch0.append(0)
                        ch1.append(0)
                        ch0[cur] = nxt
                    cur = nxt
                else:
                    nxt = ch1[cur]
                    if nxt == 0:
                        nxt = len(ch0)
                        ch0.append(0)
                        ch1.append(0)
                        ch1[cur] = nxt
                    cur = nxt
            return root

        def query_cycle(ch0, ch1, root, key):
            cur = root
            res = 0
            for bit in range(29, -1, -1):
                b = (key >> bit) & 1
                if b == 0:
                    if ch1[cur]:
                        res |= (1 << bit)
                        cur = ch1[cur]
                    else:
                        cur = ch0[cur]
                else:
                    if ch0[cur]:
                        res |= (1 << bit)
                        cur = ch0[cur]
                    else:
                        cur = ch1[cur]
            return res

        # Empty parent path for children of cycle nodes.
        base_root = insert_persistent(0, 0)

        for i in range(1, N + 1):
            if indegree[i] > 0 and not visited_cycle[i]:
                # Collect one cycle.
                cycle_nodes = []
                cur = i
                while not visited_cycle[cur]:
                    visited_cycle[cur] = True
                    cycle_nodes.append(cur)
                    cur = A[cur]

                cp = []
                cur_xor = 0
                for node in cycle_nodes:
                    cur_xor ^= V[node]
                    cp.append(cur_xor)
                X = cur_xor

                ch0 = array('i', [0])
                ch1 = array('i', [0])
                root = 0

                for x in cp:
                    root = insert_cycle(ch0, ch1, root, x)
                    root = insert_cycle(ch0, ch1, root, x ^ X)

                max_cycle = query_cycle(ch0, ch1, root, 0)

                for node in cycle_nodes:
                    ans[node] = max_cycle
                    D[node] = 0

                stack = []

                for c in cycle_nodes:
                    for u in children[c]:
                        if not is_cycle[u]:
                            tag_u = V[u]
                            root_u = base_root
                            tree_max = query_persistent(root_u, tag_u)
                            D[u] = V[u]
                            cycle_val = query_cycle(ch0, ch1, root, D[u])
                            ans[u] = tree_max if tree_max > cycle_val else cycle_val
                            stack.append((u, root_u, tag_u, D[u]))

                while stack:
                    u, root_u, tag_u, d_u = stack.pop()

                    for w in children[u]:
                        if not is_cycle[w]:
                            new_tag = tag_u ^ V[w]
                            root_w = insert_persistent(root_u, tag_u)
                            tree_max = query_persistent(root_w, new_tag)
                            D[w] = V[w] ^ d_u
                            cycle_val = query_cycle(ch0, ch1, root, D[w])
                            ans[w] = tree_max if tree_max > cycle_val else cycle_val
                            stack.append((w, root_w, new_tag, D[w]))

        out_lines.append(" ".join(str(ans[i]) for i in range(1, N + 1)))

    sys.stdout.write("\n".join(out_lines))


def read_your_input():
    return sys.stdin.buffer.read()


if __name__ == "__main__":
    solve()