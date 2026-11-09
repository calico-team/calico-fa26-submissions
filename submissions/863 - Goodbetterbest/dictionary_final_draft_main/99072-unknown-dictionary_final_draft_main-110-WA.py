import sys
from array import array


def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    it = iter(data)
    T = next(it)
    output = []

    BITS = 30
    BIT_RANGE = range(BITS - 1, -1, -1)

    for _ in range(T):
        N = next(it)

        A = [next(it) - 1 for _ in range(N)]
        V = [next(it) for _ in range(N)]

        # --------------------------------
        # 1. Find all cycle nodes
        # --------------------------------

        indeg = [0] * N

        for u in range(N):
            indeg[A[u]] += 1

        queue = [u for u in range(N) if indeg[u] == 0]

        head = 0

        while head < len(queue):
            u = queue[head]
            head += 1

            v = A[u]
            indeg[v] -= 1

            if indeg[v] == 0:
                queue.append(v)

        is_cycle = bytearray(
            1 if x > 0 else 0 for x in indeg
        )

        # --------------------------------
        # 2. Build reverse tree edges
        # --------------------------------

        children = [[] for _ in range(N)]

        for u in range(N):
            if not is_cycle[u]:
                children[A[u]].append(u)

        ans = [0] * N
        seen = bytearray(N)

        # --------------------------------
        # 3. Process every cycle
        # --------------------------------

        for s in range(N):

            if not is_cycle[s] or seen[s]:
                continue

            cyc = []
            u = s

            while not seen[u]:
                seen[u] = 1
                cyc.append(u)
                u = A[u]

            L = len(cyc)

            # Prefix XOR of cycle
            pref = [0] * (L + 1)

            for i in range(L):
                pref[i + 1] = pref[i] ^ V[cyc[i]]

            C = pref[L]

            # --------------------------------
            # 4. Build cycle binary trie
            # --------------------------------

            leftB = array('i', [0])
            rightB = array('i', [0])

            for i in range(L):

                for val in (pref[i], pref[i] ^ C):

                    node = 0

                    for b in BIT_RANGE:

                        bit = (val >> b) & 1

                        if bit == 0:

                            nxt = leftB[node]

                            if nxt == 0:
                                nxt = len(leftB)
                                leftB[node] = nxt

                                leftB.append(0)
                                rightB.append(0)

                        else:

                            nxt = rightB[node]

                            if nxt == 0:
                                nxt = len(leftB)
                                rightB[node] = nxt

                                leftB.append(0)
                                rightB.append(0)

                        node = nxt

            # --------------------------------
            # 5. Process every cycle root
            # --------------------------------

            for j in range(L):

                root = cyc[j]
                shift = pref[j + 1]

                # Persistent path trie.
                # Initially contains XOR value 0.

                leftP = array('i', [0])
                rightP = array('i', [0])

                node = 0

                for b in BIT_RANGE:

                    nxt = len(leftP)
                    leftP[node] = nxt

                    leftP.append(0)
                    rightP.append(0)

                    node = nxt

                # Stack: (node, path_xor, trie_version)

                stack = [(root, V[root], 0)]

                while stack:

                    u, q, version = stack.pop()

                    # --------------------------------
                    # 6. Query path trie
                    # --------------------------------

                    node = version
                    x = 0

                    for b in BIT_RANGE:

                        bit = (q >> b) & 1

                        if bit == 0:

                            nxt = rightP[node]

                            if nxt:
                                x |= (1 << b)
                                node = nxt
                            else:
                                node = leftP[node]

                        else:

                            nxt = leftP[node]

                            if nxt:
                                x |= (1 << b)
                                node = nxt
                            else:
                                node = rightP[node]

                    # --------------------------------
                    # 7. Query cycle trie
                    # --------------------------------

                    qq = q ^ shift

                    node = 0
                    y = 0

                    for b in BIT_RANGE:

                        bit = (qq >> b) & 1

                        if bit == 0:

                            nxt = rightB[node]

                            if nxt:
                                y |= (1 << b)
                                node = nxt
                            else:
                                node = leftB[node]

                        else:

                            nxt = leftB[node]

                            if nxt:
                                y |= (1 << b)
                                node = nxt
                            else:
                                node = rightB[node]

                    ans[u] = max(x, y)

                    # --------------------------------
                    # 8. Insert q using persistent trie
                    # --------------------------------

                    new_root = len(leftP)

                    leftP.append(leftP[version])
                    rightP.append(rightP[version])

                    old_node = version
                    new_node = new_root

                    for b in BIT_RANGE:

                        bit = (q >> b) & 1

                        if bit == 0:

                            old_child = leftP[old_node]
                            new_child = len(leftP)

                            leftP[new_node] = new_child

                        else:

                            old_child = rightP[old_node]
                            new_child = len(leftP)

                            rightP[new_node] = new_child

                        leftP.append(leftP[old_child])
                        rightP.append(rightP[old_child])

                        old_node = old_child
                        new_node = new_child

                    # --------------------------------
                    # 9. Visit children
                    # --------------------------------

                    for v in children[u]:

                        stack.append((
                            v,
                            q ^ V[v],
                            new_root
                        ))

        output.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()