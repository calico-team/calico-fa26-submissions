import sys
def main():
    d = sys.stdin.buffer.read().split(); i = 1; o = []
    for _ in range(int(d[0])):
        n, m, k = map(int, d[i:i+3]); i += 3
        p = [0] + list(map(int, d[i:i+n])); i += n
        dep = [0] * (n+1); A = [0] * 1002
        for v in range(1, n+1):
            st = []; u = v
            while u and not dep[u]: st.append(u); u = p[u]
            b = dep[u]
            for w in reversed(st): b += 1; dep[w] = b
            A[dep[v]] += 1
        best = n; s = 0
        for j in range(1, min(m, 1001) + 1):
            best = min(best, s + k*(m-j+1)); s += A[j]
        o.append(min(best, s))
    print("\n".join(map(str, o)))
main()