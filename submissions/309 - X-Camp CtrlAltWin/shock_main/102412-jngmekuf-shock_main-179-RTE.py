n = int(input())
for _ in range(n):
    count = 0
    drones, nights = map(int, input().split())
    drone_stuff = [list(input().split()) for _ in range(drones)]
    for i in range(nights):
        for j in range(drones):
            d = drone_stuff[j][3]
            if d == "N":
                drone_stuff[j][1] = int(drone_stuff[j][1]) - 1
            elif d == "E":
                drone_stuff[j][0] = int(drone_stuff[j][0]) + 1
            counted = []
            for l in drone_stuff:
                counted.append((int(l[0]), int(l[1])))
            other_counted = [set(s) for s in {frozenset(s) for s in counted}]
            num = len(counted) - len(other_counted)
        for k in range(drones):
            count += 1
        count -= num
    print(count)