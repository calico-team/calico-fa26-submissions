T = int(input())
for i in range(T):
    count = False
    lst = input().split()
    length = int(lst[0])
    types = int(lst[1])
    letters = input().split()
    guess = length * letters[0]
    letters.remove(letters[0])
    while count == False:
        rmv = False
        print(guess)
        n = list(guess)
        judge = input()
        if judge == "CORRECT":
            count = True
            break
        else:
            judge = list(judge)
        x = 0
        for i in judge: 
            if n[x] != i:
                n[x] = letters[0]
                rmv = True
            x += 1
        if rmv:
            letters.remove(letters[0])
        guess = "".join(n)
  
        
   

        
            

                





        

