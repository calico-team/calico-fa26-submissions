import sys
from collections import defaultdict

def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it)); K = int(next(it))
        groups = defaultdict(list)
        for _ in range(n):
            x = int(next(it)); y = int(next(it)); z = int(next(it))
            d = next(it)  # b'N' / b'E'
            groups[x + y].append((x, z, d == b'N'))

        blocked = 0

        for lst in groups.values():
            m = len(lst)
            if m == 1:
                continue

            Es = []
            Ns = []
            zs = []
            for x, z, is_n in lst:
                zs.append(z)
                if is_n:
                    Ns.append((x, z))
                else:
                    Es.append((x, z))
            if not Es or not Ns:
                continue

            # ---- per-group Z compression ----
            zs = sorted(set(zs))
            z_to_i = {z: i for i, z in enumerate(zs)}
            sz = len(zs)

            Es = [(x, z_to_i[z]) for x, z in Es]
            Ns = [(x, z_to_i[z]) for x, z in Ns]
            Es.sort()
            Ns.sort()

            # ---- E blocked by N : Xj in [Xi, Xi+K-1] ----
            # Fenwick over Z, inline for speed
            bit = [0] * (sz + 2)
            # local bind
            def bit_add(i, delta):
                # i : 0-based
                i += 1
                while i <= sz:
                    bit[i] += delta
                    i += i & -i

            def bit_pref(i):
                # sum [0..i], i may be -1
                if i < 0:
                    return 0
                i += 1
                s = 0
                while i:
                    s += bit[i]
                    i -= i & -i
                return s

            r = 0
            l = 0
            tot = 0
            ln = len(Ns)
            for x_i, zi in Es:
                limit = x_i + K
                while r < ln and Ns[r][0] < limit:
                    bit_add(Ns[r][1], 1)
                    tot += 1
                    r += 1
                while l < ln and Ns[l][0] < x_i:
                    bit_add(Ns[l][1], -1)
                    tot -= 1
                    l += 1
                blocked += tot - bit_pref(zi)

            # ---- N blocked by E : Xj in [Xi-K+1, Xi] ----
            bit = [0] * (sz + 2)
            r = 0
            l = 0
            tot = 0
            le = len(Es)
            for x_i, zi in Ns:
                while r < le and Es[r][0] <= x_i:
                    bit_add(Es[r][1], 1)
                    tot += 1
                    r += 1
                low = x_i - K + 1
                while l < le and Es[l][0] < low:
                    bit_add(Es[l][1], -1)
                    tot -= 1
                    l += 1
                blocked += tot - bit_pref(zi)

        out.append(str(n * K - blocked))

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()