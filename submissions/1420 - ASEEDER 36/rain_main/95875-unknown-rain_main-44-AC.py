test_cases = int(input())

for case in range(test_cases):
    n, nights = map(int, input().split())
    drones = []

    for i in range(n):
        x, y, z, direction = input().split()
        x = int(x)
        y = int(y)
        drones.append((x + y, x, direction))

    drones.sort()
    total = n * nights

    current_sum = -1
    east_position = []
    first = 0

    for coordinate_sum, x, direction in drones:
        if coordinate_sum != current_sum:
            current_sum = coordinate_sum
            east_position = []
            first = 0

        if direction == "E":
            east_position.append(x)
        else:
            while first < len(east_position) and x - east_position[first] >= nights:
                first += 1

            total -= len(east_position) - first
    print(total)