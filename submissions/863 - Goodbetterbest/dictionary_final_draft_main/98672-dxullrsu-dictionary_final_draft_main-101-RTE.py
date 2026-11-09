import sys

def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    T = next(it)
    out_lines = []
    
    for _ in range(T):
        N = next(it)
        A = [next(it) - 1 for _ in range(N)]
        V = [next(it) for _ in range(N)]

        # BITS kam karo - jitni zaroorat hai utni hi
        
        BITS = 30
        # XOR kabhi 2^BITS se bara nahi ho sakta, lekin safe ke liye 1 extra
        # Agar max_v 2^29 ke qareeb hai to 30 hi rahega

        indeg = [0] * N
        for u in range(N):
            indeg[A[u]] += 1

        queue = [u for u in range(N) if indeg[u] == 0]
        head = 0
        while head < len(queue):
            u = queue[head]; head += 1
            v = A[u]
            indeg[v] -= 1
            if indeg[v] == 0:
                queue.append(v)

        is_cycle = bytearray(1 if x > 0 else 0 for x in indeg)

        children = [[] for _ in range(N)]
        for u in range(N):
            if not is_cycle[u]:
                children[A[u]].append(u)

        ans = [0] * N
        seen = bytearray(N)

        # Precompute range for speed
        rng = range(BITS - 1, -1, -1)

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
            pref = [0] * (L + 1)
            for i in range(L):
                pref[i + 1] = pref[i] ^ V[cyc[i]]
            C = pref[L]

            # --- Cycle Trie with LIST (array se tez) ---
            leftB = [0]
            rightB = [0]
            cntB = [0]
            # inline add
            for i in range(L):
                for val in (pref[i], pref[i] ^ C):
                    node = 0
                    for b in rng:
                        bit = (val >> b) & 1
                        if bit == 0:
                            nxt = leftB[node]
                            if nxt == 0:
                                nxt = len(cntB)
                                leftB[node] = nxt
                                leftB.append(0); rightB.append(0); cntB.append(0)
                        else:
                            nxt = rightB[node]
                            if nxt == 0:
                                nxt = len(cntB)
                                rightB[node] = nxt
                                leftB.append(0); rightB.append(0); cntB.append(0)
                        node = nxt
                        cntB[node] += 1

            # --- Har cycle root ke liye ---
            for j in range(L):
                root = cyc[j]
                shift = pref[j + 1]

                leftP = [0]
                rightP = [0]
                cntP = [0]
                # add 0
                node = 0
                for b in rng:
                    nxt = leftP[node]
                    if nxt == 0:
                        nxt = len(cntP)
                        leftP[node] = nxt
                        leftP.append(0); rightP.append(0); cntP.append(0)
                    node = nxt
                    cntP[node] += 1

                stack = [(root, V[root], 0)]
                while stack:
                    u, q, state = stack.pop()
                    if state == 1:
                        # remove q
                        node = 0
                        for b in rng:
                            bit = (q >> b) & 1
                            node = leftP[node] if bit == 0 else rightP[node]
                            cntP[node] -= 1
                        continue

                    # query Path Trie -> x
                    node = 0
                    x = 0
                    for b in rng:
                        bit = (q >> b) & 1
                        want = bit ^ 1
                        nxt = leftP[node] if want == 0 else rightP[node]
                        if nxt != 0 and cntP[nxt] > 0:
                            x |= (1 << b)
                            node = nxt
                        else:
                            node = leftP[node] if bit == 0 else rightP[node]

                    # query Cycle Trie -> y
                    qq = q ^ shift
                    node = 0
                    y = 0
                    for b in rng:
                        bit = (qq >> b) & 1
                        want = bit ^ 1
                        nxt = leftB[node] if want == 0 else rightB[node]
                        if nxt != 0 and cntB[nxt] > 0:
                            y |= (1 << b)
                            node = nxt
                        else:
                            node = leftB[node] if bit == 0 else rightB[node]

                    ans[u] = x if x >= y else y

                    # add q
                    node = 0
                    for b in rng:
                        bit = (q >> b) & 1
                        if bit == 0:
                            nxt = leftP[node]
                            if nxt == 0:
                                nxt = len(cntP)
                                leftP[node] = nxt
                                leftP.append(0); rightP.append(0); cntP.append(0)
                        else:
                            nxt = rightP[node]
                            if nxt == 0:
                                nxt = len(cntP)
                                rightP[node] = nxt
                                leftP.append(0); rightP.append(0); cntP.append(0)
                        node = nxt
                        cntP[node] += 1

                    stack.append((u, q, 1))
                    for v in children[u]:
                        stack.append((v, q ^ V[v], 0))

        out_lines.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    solve()