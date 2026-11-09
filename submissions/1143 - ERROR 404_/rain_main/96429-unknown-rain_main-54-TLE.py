import sys
from collections import defaultdict

class Fenwick:
    __slots__ = ("n", "bit")
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)
    def add(self, idx, delta):
        # 0-based idx
        n = self.n
        bit = self.bit
        i = idx + 1
        while i <= n:
            bit[i] += delta
            i += i & -i
    def pref(self, idx):
        # sum [0..idx], idx may be -1
        if idx < 0:
            return 0
        s = 0
        bit = self.bit
        i = idx + 1
        while i:
            s += bit[i]
            i -= i & -i
        return s

def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it)) if data else 0
    out_lines = []
    for _ in range(t):
        n = int(next(it)); K = int(next(it))
        groups = defaultdict(list)  # S -> list of (X, Z, dir) dir 0=E,1=N
        all_z = []
        for _ in range(n):
            x = int(next(it)); y = int(next(it)); z = int(next(it))
            d = next(it).decode()
            is_n = 1 if d == 'N' else 0
            groups[x + y].append((x, z, is_n))
            all_z.append(z)
        # coordinate compress Z globally per test case
        uniq_z = sorted(set(all_z))
        z_to_i = {z: i for i, z in enumerate(uniq_z)}
        ZN = len(uniq_z)

        blocked = 0

        for lst in groups.values():
            if len(lst) == 1:
                continue
            Es = []
            Ns = []
            for x, z, is_n in lst:
                zi = z_to_i[z]
                if is_n:
                    Ns.append((x, zi))
                else:
                    Es.append((x, zi))
            if not Es or not Ns:
                continue
            Es.sort()
            Ns.sort()

            # E drones blocked by N drones: Xj in [Xi, Xi+K-1]
            bit = Fenwick(ZN)
            r = 0
            l = 0
            # Ns sorted by X
            # pointer r adds Ns with X < Xi+K, l removes Ns with X < Xi
            # we sweep Es in increasing X, pointers only move forward
            total_in_window = 0
            for x_i, zi in Es:
                while r < len(Ns) and Ns[r][0] < x_i + K:
                    bit.add(Ns[r][1], 1)
                    total_in_window += 1
                    r += 1
                while l < len(Ns) and Ns[l][0] < x_i:
                    bit.add(Ns[l][1], -1)
                    total_in_window -= 1
                    l += 1
                # count Z > zi
                le = bit.pref(zi)  # Z <= zi
                blocked += total_in_window - le

            # N drones blocked by E drones: Xj in [Xi-K+1, Xi]
            bit = Fenwick(ZN)
            r = 0
            l = 0
            total_in_window = 0
            for x_i, zi in Ns:  # Ns already sorted
                while r < len(Es) and Es[r][0] <= x_i:
                    bit.add(Es[r][1], 1)
                    total_in_window += 1
                    r += 1
                while l < len(Es) and Es[l][0] < x_i - K + 1:
                    bit.add(Es[l][1], -1)
                    total_in_window -= 1
                    l += 1
                le = bit.pref(zi)
                blocked += total_in_window - le

        out_lines.append(str(n * K - blocked))
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    solve()