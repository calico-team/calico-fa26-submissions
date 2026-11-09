from __future__ import annotations

BITS = 30
FLIP_LIMIT = 40   # bucket main humkuch cheezyn store kryn gy


def _mpx(xs):
    one = 0
    two = 0
    rep = {}
    for x in xs:
        if x:
            t = x.bit_length() - 1
            bit = 1 << t
            if one & bit:
                two |= bit
            elif not two & bit:
                one |= bit
                rep[t] = x
    two &= ~0
    one &= ~two
    res = 0
    while one | two:
        b = (one | two).bit_length() - 1
        bit = 1 << b
        if two & bit:
            return res | ((bit << 1) - 1)
        res |= bit
        one ^= bit
        x = rep[b] ^ bit
        if x:
            t = x.bit_length() - 1
            nb = 1 << t
            if (one | two) & nb:
                one &= ~nb
                two |= nb
            else:
                one |= nb
                rep[t] = x
    return res


def solve(N: int, L: list[int], R: list[int]) -> int:
    
    # kuch bits already fixed hain tou un pe zyada time waste nahi kryn gy
    # bucket ki values low to high save honghi
    # fixed bits ko remove kr dounga
    
    K = 0
    bucket = [None] * BITS
    mask = 0                         # bucked jo k h variable k sath hoghi us ko remove kr dia gaya hai
    for i in range(N):
        l = L[i]; r = R[i]
        if l == r:
            K ^= l
            continue
        h = (l ^ r).bit_length() - 1
        hi = (l >> (h + 1)) << (h + 1)
        K ^= hi
        b = bucket[h]
        if b is None:
            bucket[h] = [(l ^ hi, r ^ hi)]
            mask |= 1 << h
        else:
            b.append((l ^ hi, r ^ hi))

    # jo buckets khali nahi hain sirf un k sath hi procesing ho ghi
    #last tak hum cheezoun ko process kryn ghy
    ans = 0
    while mask:
        H = mask.bit_length() - 1
        mask ^= 1 << H
        A = bucket[H]
        if not mask and len(A) == 1:
            # Endgame: only one range [l, r] is left (l < 2^H <= r < 2^(H+1)).
            # The remaining answer bits = max over y in [l, r] of (K ^ y): standard greedy.
            l, r = A[0]
            x = 0
            b = H
            while b >= 0:
                bit = 1 << b
                if K & bit:
                    if x + bit - 1 < l:      # must set this bit of y to stay >= l
                        x |= bit
                else:
                    if x | bit <= r:         # set it if we stay <= r
                        x |= bit
                b -= 1
            return ans | (K ^ x)
        # yhn pr kam se kam iak srore pan hona chahiye
        ans |= 1 << H
        top = 1 << H
        ones = top - 1
        t = 1 ^ ((K >> H) & 1)          #upr waly pan ki kuch chahiye hoga
        K &= ~top
        if len(A) == 1:
            l, r = A[0]
            #range ko follow krna k lie aik tight loopp lga rha hon
            # half loop rkhounga jo k bit 1 maintain rkhy ga
            nxt = mask.bit_length() - 1          # baqi ka 1 ko khali nahi hai
            while True:
                if t:
                    l, r = 0, r ^ top            # next hal ki value [0, r - 2^H]
                else:
                    r = ones                     #first half ki value [l, 2^H - 1]
                if l == r:
                    K ^= l
                    l = -1
                    break
                H = (l ^ r).bit_length() - 1
                hi = (l >> (H + 1)) << (H + 1)
                K ^= hi
                l ^= hi; r ^= hi
                if H <= nxt:
                    break
                top = 1 << H
                ones = top - 1
                ans |= top
                t = 1 ^ ((K >> H) & 1)
                K &= ~top
            if l >= 0:
                b = bucket[H]
                if b is None:
                    bucket[H] = [(l, r)]
                    mask |= 1 << H
                else:
                    b.append((l, r))
            continue
        else:
            c = len(A)
            u = []; w = []; p0 = 0; tie = False
            for l, r in A:
                a = r ^ top
                s = ones - l
                if a >= s:
                    u.append(a); w.append(s); p0 ^= 1
                    if a == s:
                        tie = True
                else:
                    u.append(s); w.append(a)
            if p0 == t or tie or c > FLIP_LIMIT:
                G = _mpx(u)
            else:
                #aur yhn pr aa kr parity wrong ho gai hain
                G = 0
                for i in range(c):
                    old = u[i]; u[i] = w[i]
                    g = _mpx(u)
                    u[i] = old
                    if g > G:
                        G = g
            if (c - t) & 1:             #yhn even numbers ki jgh pr odd number loinga
                K ^= ones
            nl, nr = 0, G
        
        if nl == nr:
            K ^= nl
        else:
            h = (nl ^ nr).bit_length() - 1
            hi = (nl >> (h + 1)) << (h + 1)
            K ^= hi
            b = bucket[h]
            if b is None:
                bucket[h] = [(nl ^ hi, nr ^ hi)]
                mask |= 1 << h
            else:
                b.append((nl ^ hi, nr ^ hi))
    return ans | K
def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()