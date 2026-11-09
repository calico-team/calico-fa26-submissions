import sys

def main():
    data = sys.stdin.read().split()
    phase = data[0]
    n = int(data[1])

    if phase == "FIRST":
        if n == 2:
            print("0 0")
            return
        deg = [0] * (n + 2)
        nb = [0] * (n + 2)
        idx = 2
        for _ in range(n - 1):
            u = int(data[idx]); v = int(data[idx + 1]); idx += 2
            deg[u] += 1; deg[v] += 1
            nb[u] ^= v; nb[v] ^= u
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
        seq = []
        for _ in range(n - 2):
            p = nb[leaf]
            seq.append(p)
            deg[leaf] = 0
            deg[p] -= 1
            nb[p] ^= leaf
            if deg[p] == 1 and p < ptr:
                leaf = p
            else:
                ptr += 1
                while deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
        x = 0
        for v in seq:
            x ^= v
        seq.append(x)
        seq.append(0)
        print(" ".join(map(str, seq)))
    else:
        a = [int(t) for t in data[2:2 + n]]
        if n == 2:
            print("1 2")
            return
        miss = a.index(-1)
        if miss < n - 2:
            x = a[n - 2]
            for i in range(n - 2):
                if i != miss:
                    x ^= a[i]
            a[miss] = x
        seq = a[:n - 2]
        deg = [1] * (n + 2)
        for p in seq:
            deg[p] += 1
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
        out = []
        for p in seq:
            out.append(f"{leaf} {p}")
            deg[p] -= 1
            if deg[p] == 1 and p < ptr:
                leaf = p
            else:
                ptr += 1
                while deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
        out.append(f"{leaf} {n}")
        print("\n".join(out))

if __name__ == "__main__":
    main()
