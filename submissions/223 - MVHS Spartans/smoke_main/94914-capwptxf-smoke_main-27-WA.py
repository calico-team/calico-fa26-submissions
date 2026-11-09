for _ in range(int(input())):
    N, R = [int(i) for i in input().split()]
    A = [int(i) for i in input().split()]
    charges = 2
    next1 = 0

    for i in A:
        #print(next1)
        #print(next2)
        #print(charges)
        #print("==")
        charges -= 1
        if i-next1 >= R:
            charges += 1
            if charges == 0:
                next1 = min(next1+R, i+R)
            elif charges == 1:
                next1 = i+R


        if charges < 0:
            print("NO")
            break
    if charges >= 0:
        print("YES")
