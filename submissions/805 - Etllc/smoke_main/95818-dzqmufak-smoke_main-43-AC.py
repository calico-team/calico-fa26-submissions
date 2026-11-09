t = int(input())

for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    x = 0
    y = 0
    ans = "YES"

    for j in range(n):
        if x <= a[j]:
            x = max(a[j], y) + r
        elif y <= a[j]:
            y = max(a[j], x) + r
        else:
            ans = "NO"
            break

        if x > y:
            x, y = y, x

    print(ans)