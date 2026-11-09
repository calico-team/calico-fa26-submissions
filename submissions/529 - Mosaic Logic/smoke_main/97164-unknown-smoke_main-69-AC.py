tests = int(input())
for i in range(tests):
    n,r = map(int, input().split())
    times = list(map(int, input().split()))
    charges = 2
    ready_time = 0
    answer = "YES"
    for t in times:
        while charges < 2 and ready_time <= t:
            charges += 1
            if charges < 2:
                ready_time = ready_time + r
        if charges == 0:
            answer = "NO"
            break
        if charges == 2:
            ready_time = t+r
        charges -= 1
    print(answer)

