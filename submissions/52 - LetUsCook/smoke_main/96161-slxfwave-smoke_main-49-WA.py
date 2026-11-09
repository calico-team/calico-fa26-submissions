T = int(input())

for i in range (T) :
    N, R = list(map(int, input().split(" ")))
    A = list(map(int, input().split(" ")))

    time = 0

    smoke_1 = True
    smoke_2 = True

    smoke_1_cooldown = 0
    smoke_2_cooldown = 0

    isTrue = True

    for j in range (N - 1) :
        time += A[j]

        if (time >= smoke_1_cooldown & smoke_1 == False) :
            smoke_1 = True
        elif (time >= smoke_2_cooldown & smoke_2 == False) :
            smoke_2 = True

        if smoke_1 :
            smoke_1 = False
            smoke_1_cooldown = time + R
        elif smoke_2 :
            smoke_2 = False
            smoke_2_cooldown = smoke_1_cooldown + R
        else :
            isTrue = False
            break

    if isTrue == False :
        print("NO")
    else :
        print("YES")
