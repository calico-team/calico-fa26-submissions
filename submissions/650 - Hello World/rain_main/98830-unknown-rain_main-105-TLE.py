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

    # CONVERTING LIST OF TUPLES TO LIST OF LISTS

    L = [list(t) for t in L]
    
    unit_water = 0

    for i in range(K):

        # handling first night, coz no problem in start
        # if i == 0:
        #     # as inital has no problems
        #     unit_water += N

        #     # update coordinates
        #     for j in range(N):
        #         if L[j][3] == 'E':
        #             # east part
        #             L[j][0] = L[j][0] + 1
        #         else:
        #             # north part
        #             L[j][1] = L[j][1] + 1

        #     continue


        # [ [1, 3, 0, E]
                # [2, 2, 1, N]
                # [9, 9, 2, E] ]

        
        for k in range(N):
            one_specific_night_stats = L[k]

            # imagine its the ith drone
            x_i = one_specific_night_stats[0]
            y_i = one_specific_night_stats[1]
            z_i = one_specific_night_stats[2]
            d_i = one_specific_night_stats[3]

            # compare with other drones
            is_ok = True

            for l in range(N):
                if k == l:
                    continue

                
                x_j = L[l][0]
                y_j = L[l][1]
                z_j = L[l][2]
                d_j = L[l][3]

                if x_i == x_j and y_i == y_j and z_i < z_j:
                    # height issue, no include
                    is_ok = False
                    break

            if is_ok:
                unit_water += 1

        # done with night, noww update

        for n in range(N):
            if L[n][3] == 'E':
                L[n][0] += 1
            else:
                L[n][1] += 1

    return unit_water

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