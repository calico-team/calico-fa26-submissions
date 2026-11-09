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
def lower_bind(arr, tar):
    l = 0
    r = len(arr)
    while l < r:
        mid = (l + r) // 2
        if arr[mid] < tar:
            l = mid + 1
        else:
            r = mid
    return l
def solve(N: int, K: int, L: list):
    East = {}
    North = {}
    for x,y,z,d in L:
        s = x+y
        if d == 'E':
            if s not in East:
                East[s] = []
            East[s].append(x)
        else:
            if s not in North:
                North[s] = []
            North[s].append(x)
    
    for s in East:
        East[s].sort()
    blocked = 0
    for a in North:
        if a not in East:
            continue
        arr = East[a]
        for x in North[a]:
            alpha = lower_bind(arr, x-K+1)
            beta = lower_bind(arr, x+1)
            blocked += beta-alpha
    return N*K-blocked


    return 0

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