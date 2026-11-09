for _ in range(int(input())):
    n, k = (int(i) for i in input().split())
    a = [i for i in input().split()]
    s = ["_"]*n
    f = False
    for i in range(k):
        print(a[i]*n, flush=True)
        r = input()
        if r == "CORRECT":
            f = True
            break
        for i in range(n):
            if r[i] != "_":
                s[i] = r[i]
    if not f:
        print("".join(s))
        input()
