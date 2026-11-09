from collections import deque
array_mod = __import__('array').array

def solve():
    n = int(input())
    
    # parse input data, minus 1 for 0-indexed
    a = [x - 1 for x in map(int, input().split())]
    valList = list(map(int, input().split()))

    deg = [0] * n
    for x in a:
        deg[x] += 1

    que = deque()
    for i in range(n):
        if deg[i] == 0:
            que.append(i)

    topo_order = []
    while que:
        currNode = que.popleft()
        topo_order.append(currNode)
        nxt = a[currNode]
        deg[nxt] -= 1
        if deg[nxt] == 0:
            que.append(nxt)

    # TODO: make this cleaner later :)
    dists = [0] * n
    c_len = [0] * n
    seen = [False] * n

    for i in range(n):
        if deg[i] > 0 and not seen[i]:
            cycle = []
            curr = i
            while not seen[curr]:
                seen[curr] = True
                cycle.append(curr)
                curr = a[curr]
            l = len(cycle)
            for node in cycle:
                c_len[node] = l

    for u in reversed(topo_order):
        nxt = a[u]
        dists[u] = dists[nxt] + 1
        c_len[u] = c_len[nxt]

    # binary lifting table stuff
    LOG = (2 * n).bit_length()

    up = [array_mod('i', a)]
    tot = [array_mod('i', valList)]
    bst = [array_mod('i', valList)]

    for k in range(1, LOG):
        pu = up[k - 1]
        pt = tot[k - 1]
        pb = bst[k - 1]

        nu = array_mod('i', [0]) * n
        nt = array_mod('i', [0]) * n
        nb = array_mod('i', [0]) * n

        for i in range(n):
            mid = pu[i]
            nu[i] = pu[mid]
            nt[i] = pt[i] ^ pt[mid]
            nb[i] = max(pb[i], pt[i] ^ pb[mid])

        up.append(nu)
        tot.append(nt)
        bst.append(nb)

    out = []
    for i in range(n):
        steps = dists[i] + 2 * c_len[i]
        node = i
        current_val = 0
        mx = 0
        for k in range(LOG):
            if steps & (1 << k):
                mx = max(mx, current_val ^ bst[k][node])
                current_val ^= tot[k][node]
                node = up[k][node]
        out.append(str(mx))

    print(" ".join(out))

def main():
    try:
        tCount = int(input())
    except:
        return
    for _ in range(tCount):
        solve()

if __name__ == '__main__':
    main()