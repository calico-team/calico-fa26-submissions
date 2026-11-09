import bisect as b
for _ in range(int(input())):
    N, R = [int(i) for i in input().split()]
    A = [int(i) for i in input().split()]
    charges = 1
    nextpos = 0
    currentpos = A[0]
    while True:
        if currentpos > A[-1]:
            print("YES")
            break
        x = b.bisect_left(A, currentpos + R)
        y = b.bisect_left(A, currentpos)
        #print(x)
        #print(nextpos)
        if x-y > charges:
            print("NO")
            break
        else:
            currentpos = currentpos + R
            charges -= x-y
            charges += 1
