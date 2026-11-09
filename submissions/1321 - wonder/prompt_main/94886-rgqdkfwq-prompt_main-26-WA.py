n=int(input())
for i in range(n):
    string=input()
    if 'write_me' in string:
        print(string,'make_it_sound_human')
    elif 'what_is' in string:
        print(string,'do_not_hallucinate')
    elif 'solve' in string:
        print(string,'make_no_mistakes')
    else:
        print(string,'thank_you')
