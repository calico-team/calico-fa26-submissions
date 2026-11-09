n=int(input())
for i in range(n):
    string=input()
    if 'write_me' in string:
        print(f'{string}make_it_sound_human')
    elif 'what_is' in string:
        print(f'{string}do_not_hallucinate')
    elif 'solve' in string:
        print(f'{string}make_no_mistakes')
    else:
        print(f'{string}thank_you')
