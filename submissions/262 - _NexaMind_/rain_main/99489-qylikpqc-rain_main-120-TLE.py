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
    edrone=[]
    ndrone=[]
    for x,y,z,d in L:
        if d=="E":
            edrone.append((x,y,z))
        else:
            ndrone.append((x,y,z))
    
    rain=0

    for _ in range(K):
        maxZ={}
        for x,y,z in edrone:
            p=(x+_, y)
            if p not in maxZ or z >maxZ[p]:
                maxZ[p] = z

        for x,y, z in ndrone:
            p=(x, y+_)
            if p not in maxZ or z > maxZ[p]:
                maxZ[p]=z
        
        
        rain+= len(maxZ)
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