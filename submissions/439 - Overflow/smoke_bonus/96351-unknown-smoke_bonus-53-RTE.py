import sys

def main():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    
    it = iter(tokens)
    t = int(next(it))
    res = []

    for _ in range(t):
        n = int(next(it))
        r = int(next(it))
        a = [int(next(it)) for _ in range(n)]

        if n <= 2:
            res.append("YES")
            continue

        t0 = a[0] + r
        t1 = max(a[1], t0) + r
        valid = True

        for req in a[2:]:
            if req < t0:
                valid = False
                break
            t0, t1 = t1, max(req, t1) + r

        res.append("YES" if valid else "NO")

    sys.stdout.write("\n".join(res) + "\n")

if __name__ == "__main__":
    main()