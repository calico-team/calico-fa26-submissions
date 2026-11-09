t = int(input())
for i in range(t):
    le,tem = map(int, input().split())
    letter = list(input().split())
    for m in range(100):
        for j in range(le):
             for k in range(le):
                print(letter[j],end='')
             op=input()
             letter_temp = list(input().split())
             for k in range(le):
                 if letter_temp[k] != "_":
                     letter_correct = letter_temp[k]
    for j in letter_correct:
        print(j,end='')
