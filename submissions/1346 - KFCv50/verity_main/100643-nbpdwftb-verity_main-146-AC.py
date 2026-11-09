T = int(input())
for _ in range (T) :
    a,b=list(map(int,input().split()))
    c = input().split()
    ans = ['?']*a
    for d in c :
        guess = ''.join(
            ans[i] if ans[i] != '?' else d
            for i in range(a)
        )
        print(guess,flush=True)
        response = input().strip()

        if response == "CORRECT":
            break
        for i in range(a):
            if response[i] != "_":
                ans[i] = response[i]
