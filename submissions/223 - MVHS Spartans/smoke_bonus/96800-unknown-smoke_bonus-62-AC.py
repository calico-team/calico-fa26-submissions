import bisect as b
for _ in range(int(input())):
    N, R = [int(i) for i in input().split()]
    A = [int(i) for i in input().split()]
    A.append(9999999999999999999)

    charges = 2
    currentpos = 0
    timer = -1

    while(True):
        if currentpos >= N:
            print("YES")
            break
        if charges == 2:
            timer = A[currentpos] + R

        x = b.bisect_left(A, timer)
        # y = b.bisect_left(A, A[currentpos])
        if x-currentpos > charges:
            print("NO")
            break
        else:
            charges -= x-currentpos
            currentpos = x
            charges += 1
            timer += R