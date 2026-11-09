import sys
from array import array


def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)

    T = next(it)
    results = []

    B = 30
    bits = range(29, -1, -1)

    for _ in range(T):
        n = next(it)
        A = [next(it) - 1 for _ in range(n)]
        V = [next(it) for _ in range(n)]

        # Find cycle nodes using indegree elimination.
        indeg = [0] * n

        for u in range(n):
            indeg[A[u]] += 1

        queue = [u for u in range(n) if indeg[u] == 0]

        head = 0
        while head < len(queue):
            u = queue[head]
            head += 1

            v = A[u]
            indeg[v] -= 1

            if indeg[v] == 0:
                queue.append(v)

        is_cycle = bytearray(
            1 if x else 0 for x in indeg
        )

        # Construct reverse edges for non-cycle nodes.
        children = [[] for _ in range(n)]

        for u in range(n):
            if not is_cycle[u]:
                children[A[u]].append(u)

        ans = [0] * n
        seen = bytearray(n)

        for s in range(n):
            if not is_cycle[s] or seen[s]:
                continue

            # Extract one complete cycle.
            cyc = []
            u = s

            while not seen[u]:
                seen[u] = 1
                cyc.append(u)
                u = A[u]

            L = len(cyc)

            # Calculate cycle prefix XOR.
            pref = [0] * (L + 1)

            for i in range(L):
                pref[i + 1] = pref[i] ^ V[cyc[i]]

            C = pref[L]

            # Build cycle trie.
            lb = array('i', [0])
            rb = array('i', [0])

            for i in range(L):
                x1 = pref[i]
                x2 = x1 ^ C

                for val in (x1, x2):
                    node = 0

                    for b in bits:
                        if (val >> b) & 1:
                            nxt = rb[node]

                            if nxt == 0:
                                nxt = len(lb)
                                rb[node] = nxt
                                lb.append(0)
                                rb.append(0)

                        else:
                            nxt = lb[node]

                            if nxt == 0:
                                nxt = len(lb)
                                lb[node] = nxt
                                lb.append(0)
                                rb.append(0)

                        node = nxt

            # Process every cycle node as a tree root.
            for j in range(L):
                root = cyc[j]
                shift = pref[j + 1]

                # Path trie: initially contains zero.
                lp = array('i', [0])
                rp = array('i', [0])
                cp = array('i', [0])

                node = 0

                for b in bits:
                    nxt = len(lp)
                    lp[node] = nxt

                    lp.append(0)
                    rp.append(0)
                    cp.append(0)

                    node = nxt
                    cp[node] = 1

                # Iterative DFS.
                # state 0 = enter, state 1 = exit.
                stack = [(root, V[root], 0)]

                while stack:
                    u, q, state = stack.pop()

                    if state == 1:
                        # Remove q from path trie.
                        node = 0

                        for b in bits:
                            bit = (q >> b) & 1

                            if bit:
                                node = rp[node]
                            else:
                                node = lp[node]

                            cp[node] -= 1

                        continue

                    # Query maximum XOR in path trie.
                    node = 0
                    x = 0

                    for b in bits:
                        bit = (q >> b) & 1

                        if bit:
                            nxt = lp[node]
                            fallback = rp[node]
                        else:
                            nxt = rp[node]
                            fallback = lp[node]

                        if nxt and cp[nxt] > 0:
                            x |= 1 << b
                            node = nxt
                        else:
                            node = fallback

                    # Query maximum XOR in cycle trie.
                    z = q ^ shift
                    node = 0
                    y = 0

                    for b in bits:
                        bit = (z >> b) & 1

                        if bit:
                            nxt = lb[node]
                            fallback = rb[node]
                        else:
                            nxt = rb[node]
                            fallback = lb[node]

                        if nxt:
                            y |= 1 << b
                            node = nxt
                        else:
                            node = fallback

                    ans[u] = max(x, y)

                    # Insert q into path trie.
                    node = 0
                    cp[node] += 1

                    for b in bits:
                        bit = (q >> b) & 1

                        if bit:
                            nxt = rp[node]

                            if nxt == 0:
                                nxt = len(lp)
                                rp[node] = nxt

                                lp.append(0)
                                rp.append(0)
                                cp.append(0)

                        else:
                            nxt = lp[node]

                            if nxt == 0:
                                nxt = len(lp)
                                lp[node] = nxt

                                lp.append(0)
                                rp.append(0)
                                cp.append(0)

                        node = nxt
                        cp[node] += 1

                    # Exit event removes q after children finish.
                    stack.append((u, q, 1))

                    for v in children[u]:
                        stack.append((v, q ^ V[v], 0))

        results.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve()