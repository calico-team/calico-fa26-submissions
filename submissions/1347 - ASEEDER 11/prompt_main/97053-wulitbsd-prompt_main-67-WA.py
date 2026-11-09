times = int(input())
for i in range(times):
    speak = str(input())
    lists = speak.split(' ')
    n = len(lists)
    has_solve = False
    has_what_is = False
    has_write_me = False

    j = 0
    while j < n:
        if lists[j] == 'solve':
            has_solve = True
            j += 1
        elif j + 1 < n and lists[j] == 'what' and lists[j + 1] == 'is':
            has_what_is = True
            j += 2
        elif j + 1 < n and lists[j] == 'write' and lists[j + 1] == 'me':
            has_write_me = True
            j += 2
        else:
            j += 1

    if has_solve:
        print(speak, 'make no mistakes')
    elif has_what_is:
        print(speak,  'do not hallucinate')
    elif has_write_me:
        print(speak, "make it sound human")
    else:
        print(speak, 'thank you')
