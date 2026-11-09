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
    count = 0
    penalty = 0
    for i in range(K):
      tempLL = []
      for i in range(N):
        tempL = [L[i][0],L[i][1]]
        if(tempL in tempLL):
          penalty+=1
        else:
          tempLL.append(tempL)
        if L[i][3] == "E":
          L[i][0]+=1
        else:
          L[i][1]+=1
        count+=1
    return count-penalty

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append([int(X), int(Y), int(Z), D])

        print(solve(N, K, L))

if __name__ == '__main__':
    main()