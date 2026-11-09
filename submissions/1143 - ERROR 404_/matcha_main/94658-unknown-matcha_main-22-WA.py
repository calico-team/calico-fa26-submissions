import sys
def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0]); p = 1
    out = []
    for _ in range(t):
        n = int(data[p]); p += 1
        L = data[p:p+n]; p += n
        R = data[p:p+n]; p += n
        rs = [(int(a), int(b)) for a, b in zip(L, R)]
        ans = 0
        for b in range(29, -1, -1):
            full = (1 << (b + 1)) - 1
            m = (1 << b) - 1
            x = 0
            nxt = []
            ch = []
            done = False
            for lo, hi in rs:
                if lo == 0 and hi == full:
                    ans |= full
                    done = True
                    break
                lb = lo >> b
                hb = hi >> b
                if lb == hb:
                    x ^= lb
                    nxt.append((lo & m, hi & m))
                else:
                    ch.append((lo & m, hi & m))
            if done:
                break
            if not ch:
                ans |= x << b
                rs = nxt
                continue
            need = 1 ^ x
            def score(lo, hi):
                if lo == 0 and hi == m:
                    return 2
                if b == 0:
                    return 0
                return 1 if ((lo >> (b - 1)) & 1) == 0 and ((hi >> (b - 1)) & 1) == 1 else 0
            picks = []
            cntB = 0
            best_flip = None
            best_loss = 10
            for idx, (lo, hi) in enumerate(ch):
                sa = score(lo, m)
                sb = score(0, hi)
                if sb > sa:
                    picks.append(1); cntB += 1; loss = sb - sa
                else:
                    picks.append(0); loss = sa - sb
                if loss < best_loss:
                    best_loss = loss; best_flip = idx
            if (cntB & 1) != need:
                picks[best_flip] ^= 1
            for (lo, hi), pk in zip(ch, picks):
                nxt.append((0, hi) if pk else (lo, m))
            ans |= 1 << b
            rs = nxt
        out.append(ans)
    print("\n".join(map(str, out)))
main()