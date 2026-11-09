test_case = int(input())

for case in range(test_case):
    n, recharge_time = map(int, input().split())
    request_time = list(map(int, input().split()))

    charges = 2
    next_recharge = 0
    possible = True

    for current_time in request_time:
        while charges < 2 and next_recharge <= current_time:
            charges += 1
            next_recharge += recharge_time

        if charges == 0:
            possible = False
            break

        if charges == 2:
            next_recharge = current_time+ recharge_time

        charges -= 1

    if possible:
        print("YES")
    else:
        print("NO")
