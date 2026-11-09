t = int(input())

for _ in range(t):
    line = input().split()
    n = int(line[0])
    r = int(line[1])

    a = [int(x) for x in input().split()]

    smoke = 2
    cd = []
    ans = "YES"

    for x in a:
        while len(cd) > 0 and cd[0] <= x:
            smoke = smoke + 1
            cd.pop(0)

        if smoke == 0:
            ans = "NO"
            break

        smoke = smoke - 1

        if len(cd) == 0:
            cd.append(x + r)
        else:
            cd.append(cd[-1] + r)

    print(ans)
