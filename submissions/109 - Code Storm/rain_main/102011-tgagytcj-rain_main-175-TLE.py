
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
def solve(N:int, K:int, L:list):
    rain_collected=0
    drones=[list(drone) for drone in L]
    for night in range(K):
        for drone in range(N):
            drone_above = False
            for coords in drones:
                if drone != drones.index(coords):
                    if drones[drone][0]==coords[0] and drones[drone][1]==coords[1] and coords[2]>drones[drone][2]:
                        drone_above = True
                        break
            if not drone_above:
                rain_collected += 1
        for coords in drones:
            if coords[3]=="E":
                coords[0]+=1
            elif coords[3]=="N":
                coords[1]+=1
    return rain_collected
def main():
    T=int(input())
    for _ in range(T):
        N,K=map(int,input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X),int(Y),int(Z),D))
        print(solve(N,K,L))
if __name__=='__main__':
    main()
