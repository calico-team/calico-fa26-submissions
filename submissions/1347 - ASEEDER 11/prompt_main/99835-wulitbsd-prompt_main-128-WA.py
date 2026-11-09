times = int(input())
for i in range(times):
    speak = input().strip()
    lists = speak.split('_')
    n = len(lists)
    has_solve = False
    what = False
    write = False

    j = 0
    while j < n:
        if lists[j] == 'solve':
            has_solve = True
            j += 1
        elif j + 1 < n and lists[j] == 'what' and lists[j + 1] == 'is':
            what = True
            j += 2
        elif j + 1 < n and lists[j] == 'write' and lists[j + 1] == 'me':
            write = True
            j += 2
        else:
            j += 1

    if has_solve:
        print(f"{speak}make_no_mistakes")
    elif what:
        print(f"{speak}do_not_hallucinate")
    elif write:
        print(f"{speak}make_it_sound_human")
    else:
        print(f"{speak}thank_you")