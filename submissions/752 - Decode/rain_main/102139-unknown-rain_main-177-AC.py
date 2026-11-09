import bisect

def solve(N: int, K: int, L):
    intersections = 0
    for s in L.keys():
        drones = list(L[s])

        l = []
        for drone in drones:
            if drone[2] == "N":
                l.append(drone[0])
        l.sort()
        for drone in drones:
            if drone[2] == "E":
                intersections += bisect.bisect_right(l, drone[0] + K - 1) - bisect.bisect_right(l, drone[0])
                
    return intersections

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = {}
        for _ in range(N):
            X, Y, Z, D = input().split()
            X = int(X)
            Y = int(Y)
            if (X + Y) in L.keys():
                L[X + Y].add((X, Y, D))
            else:
                L[X + Y] = {(X, Y, D)}
        print(N * K - solve(N, K, L))

if __name__ == '__main__':
    main()
