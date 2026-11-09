def check(times, delay):
    completed = []

    for moment in times:
        if len(completed) >= 2 and moment < completed[-2]:
            return "NO"

        previous = completed[-1] if completed else 0
        completed.append(max(moment, previous) + delay)

    return "YES"


for _ in range(int(input())):
    count, delay = map(int, input().split())
    times = list(map(int, input().split()))

    print(check(times, delay))
