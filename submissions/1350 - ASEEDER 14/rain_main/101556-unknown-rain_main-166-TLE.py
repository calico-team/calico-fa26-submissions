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
            a = (1 if d1 == 'E' else 0) - (1 if d2 == 'E' else 0)
            b = (1 if d1 == 'N' else 0) - (1 if d2 == 'N' else 0)
            dx = x1 - x2
            dy = y1 - y2
            s = None

            if a == 0 and b == 0:
                continue
            elif a == 0:
                if dx != 0:
                    continue
                if (-dy) % b != 0:
                    continue
                s = (-dy) // b
            elif b == 0:
                if dy != 0:
                    continue
                if (-dx) % a != 0:
                    continue
                s = (-dx) // a
            else:
                if (-dx) % a != 0 or (-dy) % b != 0:
                    continue
                s1 = (-dx) // a
                s2 = (-dy) // b
                if s1 != s2:
                    continue
                s = s1

            if s is None or s < 0:
                continue
            t = s + 1
            if t > K:
                continue

            if z1 < z2:
                blocked.add((t, i))
            else:
                blocked.add((t, j))

    total -= len(blocked)
    return total


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            parts = input().split()
            X = int(parts[0])
            Y = int(parts[1])
            Z = int(parts[2])
            D = parts[3]
            L.append((X, Y, Z, D))
        print(solve(N, K, L))

if __name__ == '__main__':
    main()

