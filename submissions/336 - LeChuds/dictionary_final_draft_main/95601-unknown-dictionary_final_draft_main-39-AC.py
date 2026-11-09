import sys
from array import array

input = sys.stdin.readline

best = [0] * (256 * 8)
for m in range(1, 256):
    for d in range(8):
        best[m * 8 + d] = max((c for c in range(8) if m >> c & 1), key=lambda c: c ^ d)


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    w = [a - 1 for a in A]
    top_bit = max(max(V).bit_length(), 1)
    shifts = list(range((top_bit - 1) // 3 * 3, -1, -3))

    state = [0] * N
    on_cycle = [False] * N
    cycles = []
    for i in range(N):
        path = []
        x = i
        while state[x] == 0:
            state[x] = 1
            path.append(x)
            x = w[x]
        if state[x] == 1:
            cyc = path[path.index(x):]
            cycles.append(cyc)
            for c in cyc:
                on_cycle[c] = True
        for p in path:
            state[p] = 2

    children = [[] for _ in range(N)]
    for j in range(N):
        if not on_cycle[j]:
            children[w[j]].append(j)

    kids = array('i')
    mask = array('i')
    owner = array('i')

    def new_node(src, who):
        mask.append(mask[src] if src >= 0 else 0)
        kids.extend(kids[src * 8:src * 8 + 8] if src >= 0 else [0] * 8)
        owner.append(who)
        return len(mask) - 1

    def insert(root, val, who):
        top = root if owner[root] == who else new_node(root, who)
        node = top
        for s in shifts:
            d = (val >> s) & 7
            mask[node] |= 1 << d
            nxt = kids[node * 8 + d]
            if nxt == 0:
                kids[node * 8 + d] = ~val
                return top
            if nxt < 0:
                if ~nxt == val:
                    return top
                nn = new_node(-1, who)
                e = (~nxt >> (s - 3)) & 7
                mask[nn] = 1 << e
                kids[nn * 8 + e] = nxt
            elif owner[nxt] == who:
                nn = nxt
            else:
                nn = new_node(nxt, who)
            kids[node * 8 + d] = nn
            node = nn
        return top

    def query(root, val):
        node = root
        for s in shifts:
            c = best[mask[node] * 8 + ((val >> s) & 7)]
            nxt = kids[node * 8 + c]
            if nxt < 0:
                return val ^ ~nxt
            node = nxt

    g = [0] * N
    ans = [0] * N
    root = [0] * N
    line = list(range(N))

    for cyc in cycles:
        total = 0
        for c in cyc:
            g[c] = total
            total ^= V[c]

        r = new_node(-1, -1)
        for c in cyc:
            insert(r, g[c], -1)
            insert(r, g[c] ^ total, -1)
            root[c] = r

        queue = list(cyc)
        for x in queue:
            ans[x] = query(root[x] if on_cycle[x] else root[w[x]], g[x])
            if children[x] and not on_cycle[x]:
                p = w[x]
                if not on_cycle[p] and len(children[p]) == 1:
                    line[x] = line[p]
                root[x] = insert(root[p], g[x], line[x])
            for y in children[x]:
                g[y] = V[y] ^ g[x]
                queue.append(y)

    return ans


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))


if __name__ == '__main__':
    main()
