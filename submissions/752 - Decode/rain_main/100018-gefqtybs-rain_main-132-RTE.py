def solve(N: int, K: int, L):
    intersections = 0
    for s in L.keys():
        drones = list(L[s])
        l = [0] * (s + 1)
        for drone in drones:
            if drone[2] == "N":
                l[drone[0]] = 1
        curr_sum = sum(l[1:min(K, s + 1)])
        l2 = [curr_sum]
        for i in range(2, s + 1):
            curr_sum -= l[i - 1]
            if i + K - 2 <= s:
                curr_sum += l[i + K - 2]
            l2.append(curr_sum)
        for drone in drones:
            if drone[2] == "E":
                i = drone[0]
                if i != s:
                    intersections += l2[i]
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
            Z = int(Z)
            if (X + Y) in L.keys():
                L[X + Y].add((X, Y, D))
            else:
                L[X + Y] = {(X, Y, D)}
        print(N * K - solve(N, K, L))

if __name__ == '__main__':
    main()
