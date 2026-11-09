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

    collected_rain = 0;
    drons = L;

    for night in range(K):

        for i, dron in enumerate(drons):

            is_rain_blocked = False;

            for j, dron2 in enumerate(drons):

                if i == j:
                    continue

                if dron[0] == dron2[0] and dron[1] == dron2[1] and dron[2] < dron2[2]:
                    is_rain_blocked = True
                    break;

            if not is_rain_blocked:
                collected_rain+=1;

        for dron in drons:
            if(dron[3]=='E'):
                dron[0] += 1;
            else:
                dron[1] += 1;


    
    return collected_rain;



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