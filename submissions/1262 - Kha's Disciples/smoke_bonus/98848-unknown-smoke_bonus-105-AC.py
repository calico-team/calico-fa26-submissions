def solve():
    n, r = map(int, input().strip().split())
    a = list(map(int, input().strip().split()))

    s = 1
    cooldown = r
    for i in range(0,n-1):
        cooldown -= a[i+1]-a[i]
        while s < 2 and cooldown <= 0:
            cooldown += r
            s += 1
        
        if s == 2:
            cooldown = r
        if s == 0:
            print("NO")
            return
        s -= 1
    print("YES")

for _ in range(int(input())):
    solve()