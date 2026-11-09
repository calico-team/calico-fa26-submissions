T = int(input())

for _ in range(T):
    N, R = map(int, input().split())
    requests = list(map(int, input().split()))

    charges = 2
    recharge_times = []  
    possible = True

    for time in requests:
        while recharge_times and recharge_times[0] <= time:
            recharge_times.pop(0)
            charges += 1

        
        if charges == 0:
            possible = False
            break
        charges -= 1

        if recharge_times:
            recharge_times.append(recharge_times[-1] + R)
        else:
            recharge_times.append(time + R)

    print("YES" if possible else "NO")
