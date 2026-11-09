t=int(input())
for i in range(t):
    n,k=map(int,input().split())
    a=input().split()
    guess=a[0]*n
    for j in range(1,k+1):
        print(guess,flush=True)
        response=input()
        if response=='CORRECT':
            break
        character=a[j]
        guesses=[]
        for o in response:
            if o=='_':
                guesses.append(character)
            else:
                gusses.append(o)
        guess=''.join(guesses)
