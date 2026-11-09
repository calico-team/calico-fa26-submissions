for _ in range(int(input())):
    n, k = map(int,input().split())
    a = input().split()
    s = [''] * n
    ok = 0
    for x in a:
        print(x * n)
        res = input()
        if res == "CORRECT":
            ok = 1
            break
        for i in range(n):
            if res[i] == x:
                s[i] = x
    if not ok:
        print("".join(s))
        input()
