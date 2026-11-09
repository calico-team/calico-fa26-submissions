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
    total = K * N
    blocked = set()

    for i in range(N):
        x1, y1, z1, d1 = L[i]
        for j in range(i + 1, N):
            x2, y2, z2, d2 = L[j]

            if d1 == 'E':
                dx1 = 1
                dy1 = 0
            else:
                dx1 = 0
                dy1 = 1
            if d2 == 'E':
                dx2 = 1
                dy2 = 0
            else:
                dx2 = 0
                dy2 = 1

            for t in range(1, K+1):
                s = t - 1
                nx1 = x1 + dx1 * s
                ny1 = y1 + dy1 * s
                nx2 = x2 + dx2 * s
                ny2 = y2 + dy2 * s
                if nx1 == nx2 and ny1 == ny2:
                    if z1 < z2:
                        blocked.add((t, i))
                    else:
                        blocked.add((t, j))
                    break
    total -= len(blocked)
    return total


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            x, y, z, d = input().split()
            L.append((int(x), int(y), int(z), d))
        print(solve(N, K, L))

if __name__ == '__main__':
    main()
