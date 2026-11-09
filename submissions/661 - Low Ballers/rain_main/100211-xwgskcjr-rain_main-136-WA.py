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
    e = []
    n = []
    for i in L:
        if i[3] == "E":
            e.append(i)
        elif i[3] == "N":
            n.append(i)
    for i in e:
        for j in n:
            if j[0] - i[0] == i[1] - j[1] and (j[0] - i[0]) > 0 and (i[1] - j[1]) > 0 and j[0] - i[0] < K:
                total -= 1
                break
    return total

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