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
    
    east_side = []
    north_side = []
    
    for x, y, z, d in L:
        
        if d == "E":
            east_side.append((x + y, x))
            
        else:
            north_side.append((x + y, x))
            
    east_side.sort()
    north_side.sort()
    
    answer = N * K
    left_side = 0
    right_side = 0
    
    for item in east_side:
        s = item[0]
        xe = item[1]
        
        while left_side < len(north_side):
            if north_side[left_side][0] < s:
                left_side += 1
                
            elif north_side[left_side][0] == s and north_side[left_side][1] <= xe:
                left_side += 1
                
            else:
                break
            
        if right_side < left_side:
            right_side = left_side
            
        while right_side < len(north_side):
            if north_side[right_side][0] == s and north_side[right_side][1] < xe + K:
                right_side += 1
                
            else:
                break
            
        answer -= right_side - left_side
        
    return answer
    
   

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