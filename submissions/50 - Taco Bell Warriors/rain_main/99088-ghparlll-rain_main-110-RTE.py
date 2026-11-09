#N will be the number of drones and K will be the number days

import sys

class Drone:
    def __init__(self, X, Y, Z, dir):
        self.X = X
        self.Y = Y
        self.Z = Z
        self.dir = dir


def solve():
    tokens = sys.stdin.read().split()

    idx = 0
    T = int(tokens[idx])
    idx += 1
    for o in range(T):
        N = int(tokens[idx])
        K = int(token[idx+1])
        idx+=2

        drone_groups = {}

        for p in range(N):
            drone = Drone(int(tokens[idx]), int(tokens[idx+1]), int(tokens[idx+2]), tokens[idx+3])
            idx += 4
            diff = drone.X - drone.Y
            if diff not in drone_groups:
                drone_groups[diff] = {"E": [], "N": []}
            drone_groups[diff][drone.dir].append(drone)


        totalRain = N * K
        for diff, group in drone_groups.items():
            e_drones = group["E"]
            n_drones = group["N"]
            for e in e_drones:
                for n in n_drones:
                    t = n.X - e.X
                    if 0 <= t < K:
                        totalRain -=1
        print(totalRain)
solve()

        