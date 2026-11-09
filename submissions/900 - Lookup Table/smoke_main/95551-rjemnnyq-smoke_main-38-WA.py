t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    diffs = [a[0]] + [b - a for a, b in zip(a, a[1:])]
    skib = a[-1]
    curr = 2
    cd = r
    ans = "YES"
    for x in diffs:
        cd -= x
        while cd < 0 and curr < 2:
            cd += r
            curr += 1
        if cd < 0:
            cd = 0
        curr -= 1
        if curr < 0:
            ans = "NO"
            break
    print(ans)

