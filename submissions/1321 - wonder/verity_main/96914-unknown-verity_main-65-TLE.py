import random
i=int(input())
for a in range(i):
    anwser=''
    
    word=[]
    length_same=input()
    length,same=length_same.split()
    length=int(length)
    same=int(same)
    words=input().split()
    for b in words:
        word.append(b)
    result=False
    for c in range(length):
        anwser=anwser+word[random.randint(0,len(word)-1)]
    while result==False:
        guess=''
        for d in range(length):
            guess=guess+word[random.randint(0,len(word)-1)]
        print(guess)
        check=''
        count=0
        for e in range(length):
            if guess[d]==anwser[d]:
                check=check+guess[d]
                count+=1
            else:
                check=f'{check}_'
        input(check)
        if count==length:
            result=True
            input('CORRECT')
        
        
        
                
            
        
            


