import sys

def main():
    data = iter(sys.stdin.buffer.read().split())
    phase = next(data)
    n = int(next(data))
    data = map(int, data)

    if phase == b'FIRST':
        g = [[] for _ in range(n + 1)]
        for _ in range(n - 1):
            u, v = next(data), next(data)
            g[u].append(v)
            g[v].append(u)
        parent = [0] * (n + 1)
        q = [n]
        for u in q:
            for v in g[u]:
                if v != parent[u]:
                    parent[v] = u
                    q.append(v)
        check = 0
        for x in parent[1:n]:
            check ^= x
        parent[n] = check
        sys.stdout.write(' '.join(map(str, parent[1:])))
    else:
        a = list(data)
        check = 0
        for x in a:
            if x != -1:
                check ^= x
        a[a.index(-1)] = check
        sys.stdout.write('\n'.join(f'{i} {a[i - 1]}' for i in range(1, n)))

if __name__ == '__main__':
    main()