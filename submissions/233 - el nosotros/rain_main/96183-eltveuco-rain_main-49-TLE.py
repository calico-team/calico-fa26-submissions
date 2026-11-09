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
    for k in range(0, K):
        L2 = []
        for i in range(0, N):
            valid = True
            for j in range(0, N):
                if L[j][0] == L[i][0] and L[j][1] == L[i][1] and L[j][2] < L[i][2]:
                    valid = False
                    break
                
            if valid:
                count += 1
                
            newlist = list(L[i])
            
            if newlist[3] == "N":
                newlist[1] += 1
            else:
                newlist[0] += 1
                
            L2.append(newlist)
            
                
        L = L2
        
        # print("eastern west " + str(count))
        
    return count
                
                
        
        

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