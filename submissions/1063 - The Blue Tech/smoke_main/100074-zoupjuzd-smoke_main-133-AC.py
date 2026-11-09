t = int(input())

for i in range(t):
    line = input().split()
    n = int(line[0])
    r = int(line[1])

    times = input().split()

    charges = 2
    ready = 0
    answer = "YES"

    for j in range(n):
        a = int(times[j])

        while charges < 2 and ready <= a:
            charges = charges + 1
            ready = ready + r

        if charges == 0:
            answer = "NO"
            break

        if charges == 2:
            ready = a + r

        charges = charges - 1

    print(answer)