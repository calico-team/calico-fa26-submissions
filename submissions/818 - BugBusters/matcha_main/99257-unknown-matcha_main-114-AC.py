import sys
 
 
def comb(u, v):
    r = 0
    while True:
        if u < v:
            u, v = v, u
        if v == 0:
            return r + u
        tu = u.bit_length()
        if tu == v.bit_length():
            return r + (1 << tu) - 1
        r += 1 << (tu - 1)
        u -= 1 << (tu - 1)
 
 
def solve(L, R, B=30):
    D = 0
    groups = [[] for _ in range(B)]
    for l, r in zip(L, R):
        if l == r:
            D ^= l
            continue
        h = (l ^ r).bit_length() - 1
        mask = (1 << h) - 1
        D ^= ((l >> (h + 1)) << (h + 1)) | (1 << h)
        groups[h].append(((~l) & mask, r & mask))
    Y = 0
    pi = 0
    ans = 0
    for j in range(B - 1, -1, -1):
        G = groups[j]
        base = ((D >> j) & 1) ^ pi
        if (Y >> j) & 1:
            if G or base:
                ans |= (1 << (j + 1)) - 1
                break
            ans |= 1 << j
            Y -= 1 << j
            continue
        if not G:
            if base:
                ans |= 1 << j
            continue
        ans |= 1 << j
        eps = 1 ^ base
        pi ^= eps
        n = len(G)
        Ms = []
        s = 0
        for y0, y1 in G:
            if y0 > y1:
                Ms.append(y0)
                s ^= 1
            else:
                Ms.append(y1)
        if s == eps:
            for y in Ms:
                Y = comb(Y, y)
        else:
            suf = [0] * (n + 1)
            for i in range(n - 1, -1, -1):
                suf[i] = comb(suf[i + 1], Ms[i])
            pre = Y
            bestY = -1
            for i in range(n):
                y0, y1 = G[i]
                m = y0 if y0 < y1 else y1
                cand = comb(comb(pre, suf[i + 1]), m)
                if cand > bestY:
                    bestY = cand
                pre = comb(pre, Ms[i])
            Y = bestY
    return ans
 
 
def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        L = data[pos:pos + n]
        pos += n
        R = data[pos:pos + n]
        pos += n
        out.append(solve(list(map(int, L)), list(map(int, R))))
    print('\n'.join(map(str, out)))
 
 
main()