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

    sum = {}
    for a, b, c, x in L:
        if x == 'N':
            sum.setdefault(a + b, []).append(a)

    for ef in sum.values():
        ef.sort()

    def first_index(ef, value):

        lo, hi = 0, len(ef)
        while lo < hi:
            center = (lo + hi) // 2

            if ef[center] < value:
                lo = center + 1
            else:
                hi = center
        return lo

    Sessions = 0

    for a, b, c, x in L:

        if x == 'E':
            ef = sum.get(a + b)
            
            if ef:
                Sessions += first_index(ef, a + K) - first_index(ef, a)

    return N * K - Sessions


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