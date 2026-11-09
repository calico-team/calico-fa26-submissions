def can_smoke(times, recharge):
    first_ready = 0
    second_ready = 0

    for time in times:
        if time < first_ready:
            return False

        new_ready = max(time, second_ready) + recharge
        first_ready = second_ready
        second_ready = new_ready

    return True


tests = int(input())
for case in range(tests):
    n, recharge = map(int, input().split())
    times = list(map(int, input().split()))
    print("YES" if can_smoke(times, recharge) else "NO")
