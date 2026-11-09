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
    t = N*K
    sums = {}
    n = []
    for l in L:
        if l[3] == "E":
            s = l[0] + l[1]
            try:
                sums[s].append(l)
            except:
                sums[s] = [l]
        else:
            n.append(l)
    for l2 in n:
        s = l2[0] + l2[1]
        try:
            for l in sums[s]:
                t -= int(0 <= l2[0] - l[0] < K)
        except:
            pass
    return t

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