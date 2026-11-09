"""
* Return an integer denoting the amount of rain collected after the Kth nights 
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""

def solve(N: int, K: int, L: list):
    total_rain = N * K
    drones = [[x, y, z, d] for x, y, z, d in L]
    for i in range(K):
        pos_map = {}
        for index, (x, y, z, d) in enumerate(drones):
            coord = (x, y)
            if coord not in pos_map:
                pos_map[coord] = []
            pos_map[coord].append((z, index))
        
        for coord, list_z_idx in pos_map.items():
            if len(list_z_idx) > 1:
                list_z_idx.sort(key=lambda item: item[0])
                total_rain = total_rain - (len(list_z_idx) - 1)
        
        for drone in drones:
            if drone[3] == 'E':
                drone[0] += 1
            elif drone[3] == 'N':
                drone[1] += 1
        
    return total_rain

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()