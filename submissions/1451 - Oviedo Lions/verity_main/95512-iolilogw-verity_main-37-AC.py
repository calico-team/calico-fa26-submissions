for i in range(int(input())):
    n, k = map(int, input().split())
    a = input().split()
    ans = ['_'] * n

    for c in a:
        g = ''.join(x if x != '_' else c for x in ans)
        print(g, flush=True)

        s = input().strip()

        if s == "CORRECT":
            break
        for i in range(n):
            if s[i] != '_':
                ans[i] = s[i]
