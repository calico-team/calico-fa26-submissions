t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    back1 = 0
    back2 = 0
    ok = True
    for x in a:
        back = [back1, back2]
        back.sort()
        back1 = back[0]
        back2 = back[1]
        if back1 <= x:
            if back2 > x:
                back1 = back2 + r
            else:
                back1 = x + r
        else:
            ok = False
            break
    if ok:
        print("YES")
    else:
        print("NO")
