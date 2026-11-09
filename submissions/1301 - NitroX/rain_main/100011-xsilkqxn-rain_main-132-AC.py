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


import bisect

def solve(N: int, K: int, L: list) -> int:
    groups = {}
    
    # 1. Group drones by diagonal sum (X + Y)
    for x, y, z, d in L:
        diag = x + y
        if diag not in groups:
            groups[diag] = {'E': [], 'N': []}
            
        if d == 'E':
            groups[diag]['E'].append((x, y, z))
        else:
            groups[diag]['N'].append((x, y, z))
            
    blocked_count = 0
    
    # 2. Process each diagonal
    for diag, drones in groups.items():
        east_list = drones['E']
        north_list = drones['N']
        
        if not east_list or not north_list:
            continue
            
        # Sort North drones by X coordinate for fast binary search
        north_list.sort(key=lambda d: d[0])
        north_x = [d[0] for d in north_list]
        
        for x_a, y_a, z_a in east_list:
            # Time t = X_B - X_A must be in range [0, K - 1]
            # Equivalent to: X_A <= X_B <= X_A + K - 1
            min_x = x_a
            max_x = x_a + K - 1
            
            # Find the range of North drones that intersect within K nights
            left_idx = bisect.bisect_left(north_x, min_x)
            right_idx = bisect.bisect_right(north_x, max_x)
            
            # Check candidate North drones in the valid time window
            for i in range(left_idx, right_idx):
                x_b, y_b, z_b = north_list[i]
                
                # Height check: lower drone gets blocked
                if z_b > z_a or z_a > z_b:
                    blocked_count += 1

    return N * K - blocked_count


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))


if __name__ == "__main__":
    main()
