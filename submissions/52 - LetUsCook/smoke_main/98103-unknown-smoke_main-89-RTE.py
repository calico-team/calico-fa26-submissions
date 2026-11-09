T = int(input())

for i in range (T) :
    N, R = list(map(int, input().split()))
    A = list(map(int, input().split()))

    charges = 2
    readyTime = 0
    isTrue = True

    for j in range (A) :
        while charges < 2 and readyTime <= j :
            charges += 1
            if charges < 2 :
                readyTime += R

        if charges == 0 :
            isTrue - False
            break

        if charges == 2 :
            readyTime = j + R
        charges -= 1

    if isTrue == False :
        print("NO")
    else :
        print("YES")


