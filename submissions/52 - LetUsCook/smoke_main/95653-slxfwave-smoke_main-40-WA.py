T = int(input())

for i in range (T) :
    N, R = list(map(int, input().split(" ")))
    A = list(map(int, input().split(" ")))

    isTrue = True

    for j in range (N - 1) :
        if (A[j + 1] - A[j]) < R :
            isTrue = False
            break

    if isTrue == False :
        print("NO")
    else :
        print("YES")
