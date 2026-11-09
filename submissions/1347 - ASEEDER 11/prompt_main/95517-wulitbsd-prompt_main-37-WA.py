times = int(input())
for i in range(times):
    speak = str(input())
    lists = speak.split(' ')
    solve = 0
    what = 0
    write = 0
    for j in range(len(lists)):
        if lists[j] == 'solve':
            solve += 1
        elif lists[j] == 'what' and lists[j + 1] == 'is':
            what += 1
        elif lists[j] == 'write' and lists[j + 1] == 'me':
            write += 1
    if solve == 1:
        print(speak, 'make no mistakes')
    elif what == 1:
        print(speak, 'do not hallucinate')
    elif write == 1:
        print(speak, 'make it sound human')
    else:
        print(speak, 'thank you')