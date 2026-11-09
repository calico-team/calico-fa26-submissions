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

    if N == 0 or K == 0:
        return 0

    # list tuple no change

    L = [list(t) for t in L]
    
    # calculating total amount of water
    water = K * N

    # east and north drones grouped by (x + y)
    # dicts
    east_groups = {}
    north_groups = {}

    for l in range(N):
        s = L[l][0] + L[l][1]


        if L[l][3] == 'E':
            if s not in east_groups:
                east_groups[s] = []
            east_groups[s].append(L[l][0])

        else:
            if s not in north_groups:
                # make empty,
                # khali kr denge north group ko
                north_groups[s] = []

            north_groups[s].append(L[l][0])

    # they can meet if x + y is equal to each other
    for s in east_groups:
        if s not in north_groups:
            continue

        east = east_groups[s]
        north = north_groups[s]

        # no repeat checking
        east.sort()
        north.sort()


        first = last = 0

        for x_i in east:
            while first < len(north) and north[first] < x_i:
                first += 1

            while last < len(north) and north[last] <= x_i + K - 1:
                last += 1

            # height issue, lower drone loses 1 water for each meeting
            water -= last - first

    return water

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