import random

a = int(input())



for i in range(a):
    n,k = map(int,input().split())
    lst = list(map(str,input().split()))
    
    correct = False
    word = ["_"] * n
    matrix = [[False] * k for _ in range(n)]
    
    while(not correct):
        for j in range(n):
            if word[j] == "_":
                
                good = False
                while not good:
                    b = random.randint(0,k-1)
                    if matrix[j][b] == False:
                        matrix[j][b] = True
                        temp = lst[b]
                        word[j] = temp
                        good = True
         
         
         
        print(*word, sep = "")
         
        c = input()
        if c == "CORRECT":
            correct = True
            continue
        else:
            word = list(c)
    