import sys
def main():
    c = sys.stdin.buffer.read().split(); i = 1; o = []
    for _ in range(int(c[0])):
        n, m, q = map(int, c[i:i+3]); i += 3
        g = b''.join(c[i:i+n]); i += n; p = list(range(n*m))
        def f(x):
            while p[x] != x: x = p[x] = p[p[x]]
            return x
        for u in range(n*m):
            if (u+1) % m and g[u]+g[u+1] != 148: p[f(u)] = f(u+1)
            if u+m < n*m and g[u]+g[u+m] != 148: p[f(u)] = f(u+m)
        for _ in range(q):
            a, b, e, h = map(int, c[i:i+4]); i += 4
            o.append("YES" if f(a*m+b) == f(e*m+h) else "NO")
    print("\n".join(o))
main()