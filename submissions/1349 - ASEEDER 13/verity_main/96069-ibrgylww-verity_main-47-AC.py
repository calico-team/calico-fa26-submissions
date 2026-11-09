T = int(input())
for _ in range(T):
    N, K = list(map(int, input().split(' ')))
    A = input()
    A = list(A.split(' '))
    guess = []
    j = 0
    for i in range(N):
            guess.append(A[j])
    while(True):
        j += 1
        print(''.join(guess))
        pos = input()
        if pos == "CORRECT":
            break
        else:
            for i in range(N):
                if pos[i] == '_':
                    guess[i] = A[j]
                else:
                    guess[i] = pos[i]
                    
