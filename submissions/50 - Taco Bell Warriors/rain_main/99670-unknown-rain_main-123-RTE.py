import sys

class Drone:
    def __init__(self, X, Y, Z, dir):
        self.X = X
        self.Y = Y
        self.Z = Z
        self.dir = dir

def solve():
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    idx = 0
    T = int(tokens[idx])
    idx += 1
    
    results = []
    for _ in range(T):
        N = int(tokens[idx])
        K = int(tokens[idx+1])
        idx += 2

        drone_groups = {}

        for _ in range(N):
            drone = Drone(int(tokens[idx]), int(tokens[idx+1]), int(tokens[idx+2]), tokens[idx+3])
            idx += 4
            
            s = drone.X + drone.Y
            if s not in drone_groups:
                drone_groups[s] = {"E": [], "N": []}
            drone_groups[s][drone.dir].append(drone)

        totalRain = N * K
        
        for s, group in drone_groups.items():
            e_drones = group["E"]
            n_drones = group["N"]
            
            if not e_drones or not n_drones:
                continue
                
            # Sort both lists by X coordinate
            e_drones.sort(key=lambda d: d.X)
            n_drones.sort(key=lambda d: d.X)
            
            # Use a pointer (j) to keep track of North drones
            j = 0
            for e in e_drones:
                # Move j up while the North drone is too far to the left
                while j < len(n_drones) and n_drones[j].X < e.X:
                    j += 1
                
                # Check all North drones starting from j that fall within the K window
                temp_j = j
                while temp_j < len(n_drones) and n_drones[temp_j].X < e.X + K:
                    totalRain -= 1
                    temp_j += 1
                            
        results.append(str(totalRain))
        
    print('\n'.join(results))

solve()