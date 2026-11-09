for _ in range(int(input())):
    s = input()
    ss = ['write_me', 'what_is', 'solve']
    if ss[0] in s:
        print(s + 'make_it_sound_human')
    elif ss[1] in s:
        print(s + 'do_not_hallucinate')
    elif ss[2] in s:
        print(s + 'make_no_mistakes')
    else:
        print(s + 'thank_you')
