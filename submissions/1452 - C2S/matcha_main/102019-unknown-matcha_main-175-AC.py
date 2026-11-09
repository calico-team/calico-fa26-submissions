import sys


def top_bit(v):
    return v.bit_length() - 1


def solve(n, L, R):
    base = 0
    h = [-1] * n
    A = [0] * n          # option 0 offers [0, A]  (A = ~L on bits below h)
    B = [0] * n          # option 1 offers [0, B]  (B =  R on bits below h)
    group_at = [[] for _ in range(30)]

    for i in range(n):
        l, r = L[i], R[i]
        if l == r:
            base ^= l
            continue
        hi = top_bit(l ^ r)
        low = (1 << hi) - 1
        h[i] = hi
        A[i] = low ^ (l & low)
        B[i] = r & low
        base ^= l | low      # constant of option 0
        group_at[hi].append(i)

    x = [-1] * n             # -1 = still free, otherwise the fixed choice
    free_cnt = [0] * 30
    par = [0] * 30           # required parity of the free choices in a group
    bucket = [[] for _ in range(30)]   # items by the next bit where they may matter

    def place(i, below):
        # Put item i in the bucket of its highest bit that can still matter
        m = (A[i] | B[i]) if x[i] == -1 else (B[i] if x[i] else A[i])
        m &= (1 << below) - 1
        if m:
            bucket[top_bit(m)].append(i)

    def fix(i, v):
        g = h[i]
        x[i] = v
        free_cnt[g] -= 1
        par[g] ^= v
        if free_cnt[g] == 1:
            for j in group_at[g]:
                if x[j] == -1:
                    x[j] = par[g]
                    par[g] = 0
                    free_cnt[g] = 0
                    break

    P = 0
    ans = 0
    for b in range(29, -1, -1):
        g_items = group_at[b]
        if g_items:
            q = 1 ^ ((base >> b) & 1) ^ P
            P ^= q
            c1 = 1
            free_cnt[b] = len(g_items)
            par[b] = q
            if len(g_items) == 1:
                x[g_items[0]] = q
                free_cnt[b] = 0
                par[b] = 0
        else:
            c1 = ((base >> b) & 1) ^ P

        items = bucket[b]
        bucket[b] = []
        lits = []
        for i in items:
            a = (A[i] >> b) & 1
            bb = (B[i] >> b) & 1
            if a == bb:
                c1 += a
            elif x[i] != -1:
                c1 += (x[i] if bb else 1 - x[i])
            else:
                lits.append((i, bb))

        stop = False
        r = 0
        if c1 >= 2:
            stop = True
        elif c1 == 1:
            if lits:
                stop = True
            else:
                r = 1
        elif len(lits) == 1:
            r = 1
            fix(lits[0][0], lits[0][1])
        elif len(lits) >= 2:
            g = h[lits[0][0]]
            if len(lits) > 2 or h[lits[1][0]] != g or free_cnt[g] >= 3:
                stop = True
            elif (lits[0][1] ^ lits[1][1]) == par[g]:
                stop = True
            else:
                r = 1

        if stop:
            ans |= (1 << (b + 1)) - 1
            break
        ans |= r << b

        for i in items:
            place(i, b)
        for i in g_items:
            place(i, b)

    return ans


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n = int(data[pos]); pos += 1
        L = list(map(int, data[pos:pos + n])); pos += n
        R = list(map(int, data[pos:pos + n])); pos += n
        out.append(solve(n, L, R))
    sys.stdout.write("\n".join(map(str, out)) + "\n")


main()
