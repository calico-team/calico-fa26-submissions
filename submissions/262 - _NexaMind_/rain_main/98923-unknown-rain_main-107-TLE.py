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
    for t in range(K):
        cordinates=set()
        maxZ={}
        for x,y,z,d in L:
            if d == "E":
                currX=x+t
                currY=y
            elif d == "N":
                currY=y+t
                currX=x
            # cordinates.add((currX,currY))
            p=(currX, currY)
            if p not in maxZ or z > maxZ[p]:
                maxZ[p] = z

        # rain+=len(cordinates) 
        rain+=len(maxZ) 
    

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