def can_use_all_smokes(n, recharge, time):
    smokes = 2
    recharge_time = []
    next_smoke = 0

    for time in times:
        while next_smoke < len(recharge_time) and recharge_time[next_smoke] <= time:
            smokes += 1
            next_smoke += 1

        if smokes == 0:
            return "NO"

        smokes -= 1

        if recharge_time:
            start_time = max(time, recharge_time[-1])
        else:
            start_time = time

        recharge_time.append(start_time + recharge)

    return "YES"


t = int(input())

for _ in range(t):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))
    print(can_use_all_smokes(n, r, times))
