tc = int(input())
for _ in range(tc):
    n,k = map(int,input().split())
    ch = [x for x in input().split()]
    ar = [0 for i in range(n)]
    nxt = ''
    while True:
        o = ''
        for num in ar:
            o += ch[num]
        print(o,flush = True)
        nxt = input()
        if nxt == "CORRECT":
            break
        for i in range(n):
            char = nxt[i]
            if char == '_':
                ar[i]+=1

        
