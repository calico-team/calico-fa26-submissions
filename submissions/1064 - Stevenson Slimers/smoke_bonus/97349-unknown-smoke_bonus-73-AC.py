t = int(input())
for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    smokes = 1
    valid = "YES"
    for i in range(1, len(a)):
        #print(a[i], a[i-1])
        diff = a[i] - a[i-1]

        #print(f"DIFF: {diff}")
        smokes += diff / r
        if (smokes > 2):
            smokes = 2
        #print(smokes)
        smokes -= 1
        if (smokes < 0):
            valid = "NO"
            break
    
    print(valid)
        
