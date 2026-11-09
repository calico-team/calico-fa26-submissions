import bisect as b
for _ in range(int(input())):
    N, R = [int(i) for i in input().split()]
    A = [int(i) for i in input().split()]
    charges = 1
    index = 0
    nextpos = 0
    while True:
        if nextpos >= len(A):
            print("YES")
            break
        x = b.bisect_left(A, A[nextpos] + R)
        #print(x)
        #print(nextpos)
        if x-nextpos > charges:
            print("NO")
            break
        else:
            nextpos = x
            charges -= x-nextpos
