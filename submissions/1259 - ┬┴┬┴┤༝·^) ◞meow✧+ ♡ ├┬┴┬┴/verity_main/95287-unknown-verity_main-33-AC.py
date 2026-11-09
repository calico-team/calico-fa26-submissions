for _ in range(int(input())):
    n, k = map(int, input().split())
    a = input().split()
    ans = ["?" for _ in range(n)]
    for c in a:
        print(c*n, flush=True)
        w = input()
        if w == "CORRECT":
            break
        for i, d in enumerate(w):
            if d != "_":
                ans[i] = d
    else:
        print("".join(ans), flush=True)
        input()
