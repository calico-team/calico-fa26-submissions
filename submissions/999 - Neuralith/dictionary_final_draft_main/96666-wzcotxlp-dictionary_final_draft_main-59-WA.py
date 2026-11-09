
import sys
from collections import deque
from array import array


def solve():
    data = iter(read_your_input())
    t = next(data)
    output = []

    for _ in range(t):
        n = next(data)
        A = [next(data) - 1 for _ in range(n)]
        V = [next(data) for _ in range(n)]

        dinosauraus = V

        indeg = [0] * n
        for v in A:
            indeg[v] += 1

        q = deque(i for i in range(n) if indeg[i] == 0)
        order = []

        while q:
            u = q.popleft()
            order.append(u)
            v = A[u]
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)

        comp = [-1] * n
        root = [-1] * n
        tail = [0] * n
        base = [0] * n
        groups = {}

        # Find all cycles.
        for i in range(n):
            if indeg[i] > 0 and comp[i] == -1:
                cycle = []
                u = i

                while True:
                    cycle.append(u)
                    comp[u] = i
                    root[u] = u
                    u = A[u]
                    if u == i:
                        break

                pref = []
                cur = 0

                for u in cycle:
                    pref.append(cur)
                    base[u] = cur
                    cur ^= V[u]

                total = cur
                groups[i] = [cycle, pref, total, []]

        # Process the non-cycle nodes in reverse topological order.
        for u in reversed(order):
            v = A[u]
            comp[u] = comp[v]
            root[u] = root[v]
            tail[u] = V[u] ^ tail[v]
            groups[comp[u]][3].append(u)

        ans = [0] * n

        # Build a binary trie for each component.
        for representative, (cycle, pref, total, trees) in groups.items():
            left = array('i', [0, 0])
            right = array('i', [0, 0])
            size = 1

            def insert(x):
                nonlocal size
                node = 1

                for b in range(29, -1, -1):
                    bit = (x >> b) & 1

                    if bit == 0:
                        nxt = left[node]
                        if nxt == 0:
                            size += 1
                            nxt = size
                            left.append(0)
                            right.append(0)
                            left[node] = nxt
                        node = nxt
                    else:
                        nxt = right[node]
                        if nxt == 0:
                            size += 1
                            nxt = size
                            left.append(0)
                            right.append(0)
                            right[node] = nxt
                        node = nxt

            def query(x):
                node = 1
                result = 0

                for b in range(29, -1, -1):
                    bit = (x >> b) & 1

                    if bit == 0:
                        nxt = right[node]
                        if nxt:
                            result |= (1 << b)
                            node = nxt
                        else:
                            node = left[node]
                    else:
                        nxt = left[node]
                        if nxt:
                            result |= (1 << b)
                            node = nxt
                        else:
                            node = right[node]

                return result

            # Insert all cycle prefix XOR values and their complements
            # with respect to the total cycle XOR.
            for x in pref:
                insert(x)
                insert(x ^ total)

            # Answer cycle nodes.
            for j, u in enumerate(cycle):
                ans[u] = query(pref[j])

            # Answer nodes leading into the cycle.
            for u in trees:
                x = tail[u] ^ base[root[u]]
                ans[u] = query(x)

        output.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(output))


def read_your_input():
    return list(map(int, sys.stdin.buffer.read().split()))


if __name__ == "__main__":
    solve()
