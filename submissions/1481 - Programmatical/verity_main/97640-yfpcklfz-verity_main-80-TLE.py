

a = int(input())


for k in range(a):
    b = input().split()
    n = int(b[0])
    letter = input().split()
    letter = ''.join(letter)

    guess = [0] * int(b[0])
    
    for _ in range(n):

        new = [letter[i] if type(i) == int else i for i in guess]
        print(''.join(new))
        feedback = input()
        if feedback == 'CORRECT':
            break

        for w in range(len(feedback)):
            if feedback[w] == '_':
                guess[w] += 1
            else:
                guess[w] = feedback[w]
    







    

    

    
