import random

a = int(input())

for i in range(a):
    n,k = map(int,input().split())
    lst = list(map(str,input().split()))
    
    correct = False
    word = ["_"] * n
    
    while(not correct):
        for j in range(n):
            if word[j] == "_":
                b = random.randint(0,k-1)
                temp = lst[b]
                word[j] = temp
            
        print(*word, sep = "")
         
        c = input()
        if c =="CORRECT":
            correct = True
        else:
            word = list(c)
    