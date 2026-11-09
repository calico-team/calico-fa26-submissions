for _ in range(int(input())):
    n, r = tuple(int(x) for x in input().split())
    a = [int(x) for x in input().split()]
    s = 2
    cond = True
    last = 0
    for x in a:
        s += (x - last) // r
        last = x
        s = min(s, 2)
        s -= 1
        if s < 0:
            cond = False
            break
    print("YES" if cond else "NO")