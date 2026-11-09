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

    groups ={}

    for px, py, pz, way in L:

        if way =='N':
            groups.setdefault(px + py, []).append(px)

    for row in groups.values():

        row.sort()

    def lower_bound(row, target):

        left,right=0, len(row)

        while left < right:

            middle = (left + right) //2

            if row[middle] < target:

                left = middle +1

            else:

                right = middle

        return left

    hits =0

    for px, py, pz, way in L:

        if way=='E':

            row = groups.get(px + py)

            if row:

                hits += lower_bound(row, px + K) - lower_bound(row,px)

    return N * K - hits


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