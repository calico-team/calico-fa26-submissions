T = int(input())

for i in range(T) :
    l_array = []
    x_array = []
    y_array = []
    z_array = []
    d_array = []

    N, K = map(int, input().split())
    for j in range(N) :
        *coord, D = input().split()

        X, Y , Z = map(int, coord)

        x_array.append(X)
        y_array.append(Y)
        z_array.append(Z)
        d_array.append(D)

    for _ in range(N) :
        l_array.append(1)

    for k in range(K - 1) :

        for _ in range(N) :
            if d_array[_] == 'E' :
                x_array[_] += 1
            else :
                y_array[_] += 1

        coord_z = {}
        for n in range(N) :
            coord = (x_array[n], y_array[n])
            if coord not in coord_z or z_array[n] > coord_z[coord] :
                coord_z[coord] = z_array[n]

        for m in range(N) :
            coord = (x_array[m], y_array[m])
            if z_array[m] == coord_z[coord] :
                l_array[m] += 1
            else :
                l_array[m] += 0

    sum = 0

    for _ in range(N) :
            sum += l_array[_]

    print(sum)
