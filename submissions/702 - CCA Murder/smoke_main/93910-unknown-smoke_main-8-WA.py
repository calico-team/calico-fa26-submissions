t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    
    cooldown1 = 0
    cooldown2 = 0 
    prev = 0

    working = True

    for i in range(n):
        z = min(cooldown1, a[i] - prev)
        y = (a[i] - prev) - z

        cooldown1 -= z
        cooldown2 -= y
        cooldown2 = max(cooldown2, 0)

        if cooldown1 == 0:
            cooldown1 = r
        elif cooldown2 == 0:
            cooldown2 = r
        else:
            working = False 
            break 
        prev = a[i]
    
    if working:
        print('YES')
    else:
        print('NO')