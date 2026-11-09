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
    rainwater=0
    for i in range(K):
        for drone in range(N):
            rainwater+=1
            for j in range(drone,N):
                if (L[drone][0],L[drone][1])==(L[j][0],L[j][1]) and L[drone][2]<L[j][2]:
                    rainwater-=1
                    break
        for drone in range(N):
            L[drone]=list(L[drone])
            if L[drone][3]=="E":
                L[drone][0]+=1
            else:
                L[drone][1]+=1
        
    return rainwater

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