t = int(input())

for case in range(t):
    frist_line = input().split()
    n = int(frist_line[0])
    r = int(frist_line[1])

    timee = input().split()

    chrge = 2
    nxt_ready = 0
    posible = True

    for i in range(n):
        a = int(timee[i])

        
        while chrge < 2 and nxt_ready <= a:
            chrge = chrge + 1
            if chrge < 2:
                nxt_ready = nxt_ready + r

        if chrge == 0:
            posible = False
            break

        if chrge == 2:
            nxt_ready = a + r
        chrge = chrge - 1

    if posible:
        print("YES")
    else:
        print("NO")