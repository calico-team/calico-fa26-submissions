import sys


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out = []
    for _ in range(next(data)):
        n, m, k = next(data), next(data), next(data)
        g = [[] for _ in range(n + 1)]
        for i in range(1, n + 1):
            g[next(data)].append(i)

        level = g[0]
        counts = []
        while level and len(counts) < m:
            counts.append(len(level))
            level = [y for x in level for y in g[x]]

        ans = 0
        for i in range(len(counts) - 1, -1, -1):
            ans = min(ans + counts[i], (m - i) * k)
        out.append(str(ans))

    sys.stdout.write('\n'.join(out))


main()
