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
    
    meeting_group = {}
    for i in range(N):
        x, y, z, d = L[i]
        coord = x + y
        if coord not in meeting_group:
            meeting_group[coord] = []
        meeting_group[coord].append((x, y, z, d))  
    
    for coord in meeting_group:
        group = meeting_group[coord]
        east = [pos for pos in group if pos[3] == "E"]
        north = [pos for pos in group if pos[3] == "N"]
        
        
        for e in east:
            for n in north:
                total = n[0] - e[0]
                if (total >= 0) and (total < K):
                    total_rain -= 1
    
    
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