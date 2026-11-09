import random

z = int(input())

guesses = []

for y in range(z):



    w,t = input().split(' ')
    w = int(w)
    t = int(t)

    know = [None for i in range(w)]

    
    c = input().split(' ')

    

    while True:

        bla = len(know) - know.count(None)
        #print(bla)

        g = []

        while not ''.join(g) in guesses:

            g = []
            for i in range(w):
                if not know[i]:
                    g.append(c[random.randint(0,t-1)])
                else:
                    g.append(know[i])
            guesses.append(''.join(g))

        print(''.join(g))
        #print(guesses)



        correct = input()

        if correct == 'CORRECT':
            break

        for i in range(len(correct)):
            if not correct[i] == '_':
                know[i] = correct[i]

        #print(know)

        

# L C V F

# LVFC
            







