for _ in range(int(input())):
    F = 0
    n, k = map(int, input().split())
    a = input().split()
    s = ['']*n
    for i in range(k):
        print(a[i]*n)
        g = input()
        if g == 'CORRECT':
            F = 1
            break
        for c in range(n):
            if g[c] != '_':
                s[c] = g[c]
    if F:
        continue
    print(''.join(s))
    input()