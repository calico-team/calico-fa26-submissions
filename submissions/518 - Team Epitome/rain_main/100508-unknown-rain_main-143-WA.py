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
    data ={}  

    #grouping drones who meet 
    for X,Y,Z,D in L:
        position_sum = X+Y

        if position_sum not in data:
            data[position_sum] = [[],[]]

        if D == 'e':
            data[position_sum][0].append((X,Z))
        else:
            data[position_sum][1].append((X,Z))

    count = 0

    for east, north in data.values():
        east.sort()
        north.sort()

        height_count = {}
        left = 0
        right = 0

        for X,Z in east:
            # adding north drones that meet drones going east
            while right <len(north) and north[right][0]< X+K:
                height = north[right][1]
                height_count[height] = height_count.get(height, 0 )+1
                right += 1

            # removing drones that already passed the meeting point
            while left< right and north[left][0]<= X:
                height = north[left][1]
                height_count[height] -=1
                left +=1

            # drones with same height do not block one another
            count += right- left -height_count.get(Z,0)

    return N*K - count

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