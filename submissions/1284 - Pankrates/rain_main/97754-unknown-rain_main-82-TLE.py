"""
* Return an integer denoting the amount of rain collected after the Kth nights 
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone (REMOVED)
*   D: Starting direction of Drone (E or N)
"""

def solve(N: int, K: int, L: list):

    collected = 0
    used_locations = set()

    for _ in range(K):
        for drone in range(N):
            used_locations.add((L[drone][0], L[drone][1]))
            # if L[drone][2] == "E":
            #     # L[drone] = (L[drone][0] + 1, L[drone][1], L[drone][2])
            #     L[drone][0] += 1
            # else:
            #     # L[drone] = (L[drone][0], L[drone][1] + 1, L[drone][2])
            #     L[drone][1] += 1

            L[drone][L[drone][2] == "N"] += 1
        collected += len(used_locations)
        used_locations.clear()

    return collected

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append([int(X), int(Y), D])

        print(solve(N, K, L))

if __name__ == '__main__':
    main()