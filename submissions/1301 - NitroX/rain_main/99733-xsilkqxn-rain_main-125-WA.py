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
    groups = {}

    # 1. Group drones by diagonal sum (X + Y)
    for x, y, z, d in L:
        diag = x + y
        if diag not in groups:
            groups[diag] = {"E": [], "N": {}}

        if d == "E":
            groups[diag]["E"].append((x, y, z))
        else:
            # Map X_B directly to Z_B for North drones
            groups[diag]["N"][x] = z

    blocked = 0

    # 2. Check collisions
    for diag, drones in groups.items():
        east_list = drones["E"]
        north_map = drones["N"]

        if not east_list or not north_map:
            continue

        for x_a, y_a, z_a in east_list:
            # An East drone moving for K nights sweeps X from x_a to x_a + K - 1.
            # Any North drone it crosses must be at X_B = x_a + t where 0 <= t < K.
            # Since X_B uniquely identifies a North drone on this diagonal,
            # we check if any North drone exists in north_map within that X range.

            # Efficient lookup:
            for t in range(K):
                target_x = x_a + t
                if target_x in north_map:
                    if north_map[target_x] > z_a:
                        blocked += 1
                    break  # At most one North drone can be at target_x on this diagonal

    return N * K - blocked


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
