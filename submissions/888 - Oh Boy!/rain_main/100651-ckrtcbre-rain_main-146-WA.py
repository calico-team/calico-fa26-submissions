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
    collisions = 0
    east = {}
    north = {}
    sky = {}
    L = sorted(L)
    for drone in range(N):
        if sky.get(L[drone][0] + L[drone][1]) is None:
            sky[(L[drone][0] + L[drone][1])] = 1
            if L[drone][3] == 'E':
                east[(L[drone][0] + L[drone][1])] = [L[drone][0]]
                north[(L[drone][0] + L[drone][1])] = []
            else:
                north[(L[drone][0] + L[drone][1])] = [L[drone][0]]
                east[(L[drone][0] + L[drone][1])] = []

        elif sky.get((L[drone][0] + L[drone][1])) is not None:
            if L[drone][3] == 'E':

                count = 1
                while len(north[(L[drone][0] + L[drone][1])]) >= count and 0 <= L[drone][0] - north[(L[drone][0] + L[drone][1])][-count] < K:
                    collisions += 1
                    count += 1
                east[(L[drone][0] + L[drone][1])].append(L[drone][0])
            else:
                count = 1
                while len(east[(L[drone][0] + L[drone][1])]) >= count and 0 <= L[drone][0] - east[(L[drone][0] + L[drone][1])][-count] < K:
                    collisions += 1
                    count += 1
                north[(L[drone][0] + L[drone][1])].append(L[drone][0])

    return (K * N) - collisions

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