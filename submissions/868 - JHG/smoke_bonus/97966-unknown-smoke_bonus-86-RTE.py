tests = int(input())
for _ in range(tests):
    numRequests, recharge = map(int, input().split())
    requests = list(map(int, input().split()))

    charges = 2
    recharge_finish_time = float('inf')
    possible = True

    for time in requests:
        while charges < 2 and time >= recharge_finish_time:
            charges += 1
            if charges < 2:
                recharge_finish_time += recharge
            else:
                recharge_finish_time = float('inf')

        if charges > 0:
            charges -= 1
            if charges == 1 and recharge_finish_time == float('inf'):
                recharge_finish_time = time + recharge
        else:
            possible = False
            break

    if possible:
        print('Yes')
    else:
        print('No')
