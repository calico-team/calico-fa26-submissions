cases = int(input())

for i in range(cases):
    n, k = map(int,input().split())

    drones = []

    for j in range(n):
        inp = input().split()
        drones.append([
            [int(inp[0]),int(inp[1])],
            inp[3]
        ])

    rain = len(drones)

    for j in range(k-1):
        dm = set()
        for ind,l in enumerate(drones):
            l[0][0] += int(l[1] != "N")
            l[0][1] += int(l[1] == "N")

            dm.add(l[0][0] * pow(2,32) + l[0][1])

        rain += len(dm)

    print(rain)