t = int(input())

for i in range(t):
    line = input().split()
    n = int(line[0])
    k = int(line[1])

    east = []
    north = []

    for j in range(n):
        parts = input().split()
        x = int(parts[0])
        y = int(parts[1])
        d = parts[3]

        if d == "E":
            east.append((x, y))
        else:
            north.append((x, y))

    meetings = 0

    for a in east:
        for b in north:
            x1 = a[0]
            y1 = a[1]
            x2 = b[0]
            y2 = b[1]

            day = x2 - x1
            if day == y1 - y2 and day >= 0 and day <= k - 1:
                meetings = meetings + 1

    print(n * k - meetings)