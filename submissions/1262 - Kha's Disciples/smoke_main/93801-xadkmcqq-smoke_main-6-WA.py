

def solve():
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    s = 1
    cooldown = r
    for i in range(1,n):
        cooldown -= a[i]-a[i-1]
        while s < 2 and cooldown < 0:
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
