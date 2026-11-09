import sys


def phase1(n, data):
    head = [-1] * (n + 1)
    nxt = [0] * (2 * n)
    to = [0] * (2 * n)
    k = 0
    p = 2
    for _ in range(n - 1):
        u = int(data[p])
        v = int(data[p + 1])
        p += 2
        to[k] = v
        nxt[k] = head[u]
        head[u] = k
        k += 1
        to[k] = u
        nxt[k] = head[v]
        head[v] = k
        k += 1
    par = [0] * (n + 1)
    seen = [False] * (n + 1)
    seen[1] = True
    order = [1]
    i = 0
    while i < len(order):
        u = order[i]
        i += 1
        e = head[u]
        while e != -1:
            w = to[e]
            if not seen[w]:
                seen[w] = True
                par[w] = u
                order.append(w)
            e = nxt[e]
    a = [0] * n
    s = 0
    for v in range(2, n + 1):
        a[v - 1] = par[v] - 1
        s += par[v] - 1
    a[0] = n + s % n
    return ' '.join(map(str, a)) + '\n'


def phase2(n, data):
    a = [int(x) for x in data[2:2 + n]]
    j = -1
    r = -1
    for i in range(n):
        if a[i] < 0:
            j = i
        elif a[i] >= n:
            r = i
    out = []
    if r == -1:
        for i in range(n):
            if i != j:
                out.append('%d %d' % (i + 1, a[i] + 1))
    else:
        s = 0
        for i in range(n):
            if i != j and i != r:
                s += a[i]
        a[j] = (a[r] - n - s) % n
        for i in range(n):
            if i != r:
                out.append('%d %d' % (i + 1, a[i] + 1))
    return '\n'.join(out) + '\n'


def main():
    data = sys.stdin.buffer.read().split()
    phase = data[0].decode()
    n = int(data[1])
    if phase == 'FIRST':
        sys.stdout.write(phase1(n, data))
    else:
        sys.stdout.write(phase2(n, data))


main()
