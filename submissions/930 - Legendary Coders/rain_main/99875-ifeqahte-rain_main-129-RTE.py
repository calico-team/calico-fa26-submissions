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
    tl=N*K

    for i in range(N):
        a,b,c,d=L[i]
        for j in range(i+1,N):
            a1,b1,c1,d1=L[j]

            if d==d1:
                continue
            
            if a+b != a1+b1:
                continue
            
            if d=='E':
                t=a1-a
            else:
                t=a-a1

            if 0<=t<K:
                if c<c1:
                    tl-=1
                elif c1<c:
                    total-=1
    return tl


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