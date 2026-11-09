t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    skib = a[-1]
    a = set(a)
    curr = 2
    cd = r
    ans = "YES"
    for x in range(1, skib + 1):
        cd -= 1
        if cd <= 0 and curr != 2:
            cd = r
            curr += 1
        if x in a:
            curr -= 1
            if curr < 0:
                ans = "NO"
                break
    print(ans)

