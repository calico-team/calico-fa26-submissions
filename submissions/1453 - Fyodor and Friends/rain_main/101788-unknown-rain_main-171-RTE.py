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
    water = N
    print(water)
    for k in range(K - 1):
        for i in range(len(L)):
            if L[i][3] == 'E':
                L[i][0] += 1
                #print(f'x - {L[i][0]}')
            if L[i][3] == 'N':
                L[i][1] += 1
                #print(f'y - {L[i][1]}')
            isCovered = False
            for j in range(len(L)):
                
                if i != j:
                    
                    x = L[i][0]
                    y = L[i][1]
                    z = L[i][2]
                    x1 = L[j][0]
                    y1 = L[j][1]
                    z1 = L[j][2]

                    if x == x1 and y == y1:
                        if z > z1:
                            isCovered = True
                            
            if isCovered == False:
                water +=1
            

        print(water)

    return water

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