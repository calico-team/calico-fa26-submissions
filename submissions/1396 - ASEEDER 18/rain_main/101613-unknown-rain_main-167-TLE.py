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
    rain = 0
    list = []
    new = []
    new1 = []
    for i in range(N):
        new1.append(L[i][0])
        new1.append(L[i][1])
        new1.append(L[i][2])
        new.append(new1)
        new1 = []
    for j in range(N):
        if new[j] not in list:
            list.append(new[j]) 
    for j in range(len(list)):
        for k in range(j+1,len(list)):
            if list[j][0] == list[k][0] and list[j][1] == list[k][1]:
                rain -=1
    rain += len(list)
    list = []
    if K >=2:
        for i in range(K-1):
            for j in range(N):
                if L[j][3] == "N":
                    new[j][1] += 1
                if L[j][3] == "E":
                    new[j][0] += 1
            for j in range(N):
                if new[j] not in list:
                    list.append(new[j]) 
            for j in range(len(list)):
                for k in range(j+1,len(list)):
                    if list[j][0] == list[k][0] and list[j][1] == list[k][1]:
                        rain -=1
            rain += len(list)
            list = []
    return rain

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