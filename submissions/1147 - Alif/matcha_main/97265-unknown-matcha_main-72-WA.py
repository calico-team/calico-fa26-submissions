import sys

def add(basis, x):
    for bit in range(29, -1, -1):
        if (x >> bit) & 1:
            if basis[bit]:
                x ^= basis[bit]
            else:
                basis[bit] = x
                break

def best(x, basis, low=0):
    for bit in range(29, low - 1, -1):
        if basis[bit] and (x ^ basis[bit]) > x:
            x ^= basis[bit]
    return x | ((1 << low) - 1)

def go(L, R):
    n = len(L)
    diff = [L[i] ^ R[i] for i in range(n)]

    base = 0
    for x in L:
        base ^= x

    lim = (1 << max(R).bit_length()) - 1

    basis = [0] * 30
    owner = [-1] * 30

    for i, d in enumerate(diff):
        x = d
        for bit in range(29, -1, -1):
            if (x >> bit) & 1:
                if basis[bit]:
                    x ^= basis[bit]
                else:
                    basis[bit] = x
                    owner[bit] = i
                    break

    indep = {i for i in owner if i != -1}
    need = indep.copy()

    for i, d in enumerate(diff):
        if i in indep:
            continue
        x = d
        for bit in range(29, -1, -1):
            if (x >> bit) & 1:
                x ^= basis[bit]
                need.discard(owner[bit])

    ans = best(base, basis)
    if ans == lim:
        return ans

    for i in range(n):
        l, r = L[i], R[i]
        if r - l <= 1:
            continue

        if i in need:
            b = [0] * 30
            for bit in range(29, -1, -1):
                j = owner[bit]
                if j != -1 and j != i:
                    add(b, diff[j])
        else:
            b = basis

        x = l
        while x <= r:
            size = (x & -x) if x else (1 << 30)
            while size > r - x + 1:
                size //= 2
            k = size.bit_length() - 1

            v = base ^ l ^ x
            ans = max(ans, best(v, b, k))
            if ans == lim:
                return ans

            x += size

    return ans

def main():
    d = list(map(int, sys.stdin.buffer.read().split()))
    t = d[0]
    p = 1
    res = []

    for _ in range(t):
        n = d[p]; p += 1
        L = d[p:p+n]; p += n
        R = d[p:p+n]; p += n
        res.append(str(go(L, R)))

    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()