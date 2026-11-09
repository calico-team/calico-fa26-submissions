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

    total = N * K

    for k in range (1, K+1):
        total = total - overlaps(L)

        newm = []

        for drone in L:
            newr = [drone[0], drone[1], drone[2], drone[3]]
            if drone[3] == 'E':
                newr[0] = newr[0] + 1
            if drone[3] == 'N':
                newr[1] = newr[1] + 1
        newm.append(newr)

        L = newm


    return total


def overlaps (L: list):

    result = 0

    for drone1 in L:
        for drone2 in L:
            if drone1[2] >= drone2[2]:
                continue          

            if drone1[0] == drone2[0] and drone1[1] == drone2[1] and drone1[2] == drone2[2]:
                continue

            if drone1[0] == drone2[0] and drone1[1] == drone2[1]:
                result = result + 1
    
    return result


print (solve(3, 3, [[0, 3, 0, 'E'], [2, 1, 1, 'N'], [8, 8, 2, 'E'] ]))










"""
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
"""