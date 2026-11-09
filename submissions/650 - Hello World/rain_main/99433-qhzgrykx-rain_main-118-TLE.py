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

    # list tuple no change

    L = [list(t) for t in L]
    
    # calculating total amount of water
    water = K * N

    for k in range(N):
        one_specific_night_stats = L[k]

        # imagine its the ith drone
        x_i = one_specific_night_stats[0]
        y_i = one_specific_night_stats[1]
        z_i = one_specific_night_stats[2]
        d_i = one_specific_night_stats[3]

        # only east drone is picked here, it will chase the north drones
        # if east not need to worry
        if d_i != 'E':
            continue

        # compare with other drones to verify height thing
        for l in range(N):
            if k == l:
                continue

            # getting other drone number
            x_j = L[l][0]
            y_j = L[l][1]
            z_j = L[l][2]
            d_j = L[l][3]

            # same skip
            if d_j != 'N':
                continue

            # they can meet only if x + y is same
            if x_i + y_i != x_j + y_j:
                continue

            moves_req = x_j - x_i

            if 0 <= moves_req:
                if moves_req <= K - 1:
                    # height issue, lower drone loses 1 water
                    water -= 1
                    # minusing from total water

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