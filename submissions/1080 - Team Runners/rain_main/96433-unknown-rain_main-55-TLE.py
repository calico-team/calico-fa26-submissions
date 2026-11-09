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

def solve(N: int, K: int, EL: list, NL: list):
    overlaps = 0
    for northDrone in NL:
        for eastDrone in EL:
            intersectionX = northDrone[0] - eastDrone[0]
            intersectionY = eastDrone[1] - northDrone[1]
            if intersectionX == intersectionY and intersectionY < K and intersectionY > 0:
                overlaps += 1
    return N*K - overlaps

    # overlaps = 0
    # for northDrone in NL:
    #     for eastDrone in EL:
    #         print("Checking")
    #         print(northDrone)
    #         print(eastDrone)
    #         print("-----")
    #         intersectionX = northDrone[0] - eastDrone[0]
    #         intersectionY = eastDrone[1] - northDrone[1]
    #         print(intersectionX)
    #         print(intersectionY)
    #         if intersectionX == intersectionY and intersectionY < K:
    #             overlaps += 1
    #             print("overlap")
    #         print("-----")
    # return N*K - overlaps

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        EL, NL = [], []
        for _ in range(N):
            X, Y, Z, D = input().split()
            if D == "E":
                EL.append((int(X), int(Y), int(Z)))
            else:
                NL.append((int(X), int(Y), int(Z)))

        print(solve(N, K, EL, NL))

if __name__ == '__main__':
    main()