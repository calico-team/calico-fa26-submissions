t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))
    is_possible = True
    left = 2
    for i in range(n - 1):
        diff = times[i + 1] - times[i]
        if diff < r:
            left -= 1
            if left == 0:
                is_possible = False
                break
    if is_possible:
        print("YES")
    else:
        print("NO")