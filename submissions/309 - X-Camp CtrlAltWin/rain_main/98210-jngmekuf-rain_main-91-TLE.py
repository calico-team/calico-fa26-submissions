n = int(input())
for _ in range(n):
    count = 0
    drones, nights = map(int, input().split())
    drone_stuff = [list() for _ in range(drones)]
    for i in range(drones):
        l = list(input().split())
        x = int(l[0])
        y = int(l[1])
        z = int(l[2])
        d = l[3]
        drone_stuff[i] += [x, y, z, d, 1]
    for i in range(nights):
        for j in range(drones):
            if d == "N":
                drone_stuff[j][1] = drone_stuff[j][1] - 1
            elif d == "E":
                drone_stuff[j][0] = drone_stuff[j][0] + 1
            counted = []
            for l in drone_stuff:
                counted.append((l[0], l[1]))
            other_counted = [set(s) for s in {frozenset(s) for s in counted}]
            num = len(counted) - len(other_counted)
        for k in range(drones):
            count += 1
        count -= num
    print(count)