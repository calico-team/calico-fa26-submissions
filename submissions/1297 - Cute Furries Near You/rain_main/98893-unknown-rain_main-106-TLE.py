for _ in range(int(input())):
    n, k = tuple(int(x) for x in input().split())
    d = [tuple(input().split()) for _ in range(n)]
    d = [(int(x[0]), int(x[1]), int(x[2]), x[3]) for x in d]
    r = 0
    for i in range(k):
        z = set((x[0], x[1]) for x in d)
        r += len(z)
        d = [(
            x[0] + int(x[3] == 'E'),
            x[1] + int(x[3] == 'N'),
            x[2],
            x[3],
        ) for x in d]
    print(r)