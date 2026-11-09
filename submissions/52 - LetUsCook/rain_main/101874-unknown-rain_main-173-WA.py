import sys

input = sys.stdin.read().split()

if input :
    it = iter(input)
    for _ in range(int(next(it))) :
        N, K = int(next(it)), int(next(it))
        G = {}
        for i in range(N) :
            X, Y, Z, D = int(next(it)), int(next(it)), int(next(it)), next(it)
            G.setdefault(X + Y, ([], []))[D== "N"].append((X, Z))

        rain = N * K

        for E, N_lst in G.values() :
            if len(E) > 0 and len(N_lst) >0 :
                for X_e, Z_e in E :
                    for X_n, Z_n in N_lst :
                        match = (X_e <= X_n) and (X_n <= X_e + K)
                        higher = Z_e < Z_n

                        if match and higher :
                            rain -= 1

        print(rain)
