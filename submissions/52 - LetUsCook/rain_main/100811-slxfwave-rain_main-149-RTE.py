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

            for m in range(N) :
                overlap = False

                for n in range(N) :
                    if x_array[m] == x_array[n] and y_array[m] == y_array[n] :
                        if z_array[m] > z_array[n] :
                            overlap = True
                            break
                if not overlap :
                    l_array[m] += 1
                else :
                    l_array[n] += 0

        for _ in range(N) :
            sum += l_array[_]

        print(sum)
