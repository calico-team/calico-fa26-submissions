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
    answer = 0
    for t in range(1, K + 1):
        positions = set()
        for x, y, z, d in L:
            if d == 'E':
                x += t - 1
            else:
                y += t - 1
            positions.add((x, y))
        answer += len(positions)
    return answer

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