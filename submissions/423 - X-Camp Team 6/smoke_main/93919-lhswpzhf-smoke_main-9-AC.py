for thing in range(int(input())):
    n, r = map(int, input().split())
    lst = list(map(int, input().split()))
    charges = 2
    nextt = 10**9+10200202020
    flag = True 
    for i in lst:
        while nextt <= i:
            charges += 1
            if charges == 1:
                nextt = nextt+r
            else:
                nextt = 10**9+102002020202020
        if charges == 0:
            flag = False
            break
        if charges == 2:
            nextt = i+r
        charges -= 1
    if flag:
        print("YES")
    else:
        print("NO")