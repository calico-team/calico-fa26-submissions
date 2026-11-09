times = int(input())
for i in range(times):
    speak = input().strip()
    lists = speak.split('_')
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
        print(f"{speak}make_no_mistakes")
    elif has_what_is:
        print(f"{speak}do_not_hallucinate")
    elif has_write_me:
        print(f"{speak}make_it_sound_human")
    else:
        print(f"{speak}thank_you")