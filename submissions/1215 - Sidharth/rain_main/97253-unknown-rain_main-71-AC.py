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
from bisect import bisect_left
from bisect import bisect_right

def solve(N: int, K: int, L: list):
    total=N*K
    east_groups={}
    north_groups={}
    for drone in L:
        x=drone[0]
        y=drone[1]
        d=drone[3]
        s=x+y
        if d == 'E':
            if s not in east_groups:
                east_groups[s]=[]

            east_groups[s].append(x)
        else:
            if s not in north_groups:
                north_groups[s]=[]
            north_groups[s].append(x)

    blocked=0
    for s in east_groups:
        if s not in north_groups:
            continue
        east_xs=east_groups[s]
        north_xs=north_groups[s]
        north_xs.sort()
        
        for ex in east_xs:
            low = bisect_left(north_xs, ex)
            high = bisect_right(north_xs, ex+K-1)
            blocked+=high-low
            
    return total-blocked

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