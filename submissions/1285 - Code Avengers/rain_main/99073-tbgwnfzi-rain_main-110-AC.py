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
    diag = {}
    for px, py, pz, dr in L:
        pair = diag.setdefault(px + py, ([], []))
        pair[0 if dr == 'E' else 1].append(px)
    lost = 0
    for eastX, northX in diag.values():
        if not eastX or not northX:
            continue
        eastX.sort()
        northX.sort()
        left = right = 0
        cnt = len(northX)
        for ex in eastX:
            while left < cnt and northX[left] <= ex:
                left += 1
            while right < cnt and northX[right] <= ex + K - 1:
                right += 1
            if right > left:
                lost += right - left
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