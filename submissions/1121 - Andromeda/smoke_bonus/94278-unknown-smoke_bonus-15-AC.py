import sys


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


read = sys.stdin.buffer.readline
tests = int(read())

for case in range(tests):
    n, recharge = map(int, read().split())
    times = map(int, read().split())
    print("YES" if can_smoke(times, recharge) else "NO")
