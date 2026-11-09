t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))
    is_possible = True
    left = 2
    time_left = r
    for i in range(n - 1):
        while time_left <= 0:
            time_left += r
            left += 1
        if i != 0:
            time_left -= (times[i] - times[i - 1])
        else:
            time_left -= times[i]
        diff = times[i + 1] - times[i]
        if diff < r:
            if left == 0:
                is_possible = False
                break
        left -= 1
    if is_possible:
        print("YES")
    else:
        print("NO")