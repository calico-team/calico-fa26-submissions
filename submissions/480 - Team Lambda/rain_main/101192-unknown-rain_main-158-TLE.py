T = int(input())
for i in range(T):
    (N, K) = tuple(map(int, input().strip().split()))
    drones = list()
    east_drones = list()
    north_drones = list()
    total = N * K
    intersections = 0
    for i in range(N):
        drone = list(input().strip().split())
        drone[0] = int(drone[0])
        drone[1] = int(drone[1])
        drone[2] = int(drone[2])
        drones.append(drone)
        if drone[3] == "E":
            east_drones.append(drone)
        else:
            north_drones.append(drone)
    for drone1 in east_drones:
        for drone2 in north_drones:
            (x1, y1) = (drone1[0], drone1[1]) #east facing drone
            (x2, y2) = (drone2[0], drone2[1]) #north facing drone
            if x1<x2 and y1>y2:
                if abs(x1-x2) == abs(y1-y2):
                    if abs(x1-x2)<K:
                        intersections += 1
                else:
                    continue
            else:
                continue
    print(total-intersections)

