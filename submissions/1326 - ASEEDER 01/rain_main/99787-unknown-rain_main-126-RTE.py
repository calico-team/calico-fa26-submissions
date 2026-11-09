T = int(input())
NK = input().split()
N = int(NK[0])
K = int(NK[1])
for test in range(T):
    drones = []
    rain = 0
    for i in range(N):
        new = list(input().split())
        drones.append(new)
    exist = []
    for index in range(len(drones)):
        if drones[index][0:2] in exist:
            continue
        else:
            exist.append(drones[index][0:2])
    rain += len(drones)-len(exist)
    for i in range(K):
        for i in range(len(drones)):
            if drones[i][3] == 'N':
                drones[i][1] = int(drones[i][1])+1
            if drones[i][3] == 'E':
                drones[i][0] = int(drones[i][0])+1
            exist = []
            for index in range(len(drones)):
                if drones[index][0:2] in exist:
                    continue
                else:
                    exist.append(drones[index][0:2])
                rain += len(drones)-len(exist)
    print(rain)