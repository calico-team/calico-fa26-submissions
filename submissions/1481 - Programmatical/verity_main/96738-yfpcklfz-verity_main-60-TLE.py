
import itertools
a = int(input())

b = input().split()

n = int(b[1])

letter = input().split()
letter = ''.join(letter)
letter = itertools.permutations(letter)
letter = ["".join(p) for p in letter]

first = 0
for _ in range(n):
    word = letter[first]
    answer = input()
    if answer == 'CORRECT':
        break

    digit = []

    for w in range(len(answer)):
        if answer[w] != '_':
            digit.append(w)

    while True:
        check = True
        first += 1
        new = letter[first]

        for j in digit:
            if new[j] != answer[j]:
                check = False
                break
        if check:
            break
    print(new)








    

    

    
