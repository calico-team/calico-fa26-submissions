t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    alph = list(map(str, input().split()))
    
    res = '_' * n

    for i in range(len(alph)):
        guess = res.replace('_', alph[i])
        print(guess)
        res = str(input())
        if res == 'CORRECT':
            break
        
