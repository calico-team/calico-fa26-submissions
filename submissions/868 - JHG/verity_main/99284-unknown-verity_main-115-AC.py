tries = int(input())
for i in range(tries):
    n, k = map(int,input().split())
    letters = list(map(str,input().split()))

    vis = set()
    
    guesses = [['.'] for _ in range(n)]
    response = ['_'] * n
    for i in range(100):
        guess = []
        for j in range(n):
            if response[j] == '_':
                for l in range(k): 
                    if letters[l] not in guesses[j]:
                        guess.append(letters[l])
                        guesses[j].append(letters[l])
                        break
            else:
                guess.append(response[j])
        print(*guess,sep = '')
        response = input()
        if response == "CORRECT":
            break
    

                
        
    