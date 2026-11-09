dih = int(input())

for i in range(dih):
    a, b = map(int, input().split())
    fih = input().split()
    ans = [fih[0]] * a
    st = False
    n = 0
    while not st:
        print("".join(ans), flush=True)
        j = input()
        if j == "CORRECT":
            st = True
            break
        ans = list(j)
        for p in range(len(ans)):
            if ans[p] == "_":
                n += 1
                ans[p] = fih[n % b]

            

    
                


               



        



