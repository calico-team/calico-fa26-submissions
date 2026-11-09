for _ in range(int(input())):
    n, k = map(int, input().split())
    a = input().split()
    ans = ["?" for _ in range(n)]
    for c in a:
        print(c*n, flush=True)
        w = input()
        for i, d in enumerate(w):
            if d != "_":
                ans[i] = d
    print(ans, flush=True)
    input()
