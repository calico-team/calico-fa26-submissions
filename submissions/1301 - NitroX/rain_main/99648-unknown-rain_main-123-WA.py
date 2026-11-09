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
    # 1. Group drones by diagonal sum (X + Y) using a regular dictionary
    groups = {}
    for x, y, z, d in L:
        diagonal_key = x + y
        if diagonal_key not in groups:
            groups[diagonal_key] = {"E": [], "N": []}
        groups[diagonal_key][d].append((x, y, z))

    blocked = 0

    # Find starting index
    def binary_search_left(arr, target):
        low, high = 0, len(arr)
        while low < high:
            middle = (low + high) // 2
            if arr[middle] < target:
                low = middle + 1
            else:
                high = middle
        return low

    # Find ending index
    def binary_search_right(arr, target):
        low, high = 0, len(arr)
        while low < high:
            middle = (low + high) // 2
            if arr[middle] <= target:
                low = middle + 1
            else:
                high = middle
        return low

    # Checking each diagonal group
    for diag, drones in groups.items():
        east_list = drones["E"]
        north_list = drones["N"]

        if not east_list or not north_list:
            continue

        # Sorting and Precomputing Heights
        north_list.sort(key=lambda item: item[0])
        north_x = [d[0] for d in north_list]
        north_z = [d[2] for d in north_list]

        # Precompute maximum height (Z) from right to left
        total_north = len(north_z)
        max_z_from_right = [0] * total_north
        max_z_from_right[-1] = north_z[-1]
        for i in range(total_north - 2, -1, -1):
            max_z_from_right[i] = max(north_z[i], max_z_from_right[i + 1])

        for x_a, y_a, z_a in east_list:
            min_x = x_a
            max_x = x_a + K - 1

            left_index = binary_search_left(north_x, min_x)
            right_index = binary_search_right(north_x, max_x) - 1

            if left_index <= right_index:
                if right_index == total_north - 1:
                    highest_z = max_z_from_right[left_index]
                else:
                    highest_z = max(north_z[left_index : right_index + 1])

                if highest_z > z_a:
                    blocked += 1
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
