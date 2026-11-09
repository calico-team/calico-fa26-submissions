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
    from bisect import bisect_left, bisect_right

    e_drones = {} 
    n_drones = {}  

    for x, y, z, d in L:
        key = x + y
        if d == 'E':
            if key not in e_drones:
                e_drones[key] = []
            e_drones[key].append(x)
        else:
            if key not in n_drones:
                n_drones[key] = []
            n_drones[key].append(x)

    lost = 0
    for key in n_drones:
        if key not in e_drones:
            continue
        xs = sorted(e_drones[key])
        for nx in n_drones[key]:
            lo = bisect_left(xs, nx - K + 1)
            hi = bisect_right(xs, nx)
            lost += hi - lo

    return N * K - lost

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