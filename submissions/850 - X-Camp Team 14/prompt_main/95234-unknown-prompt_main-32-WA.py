t = int(input())
s = []
for i in range(t):
    s.append(input())
for i in s:
    if 'write_me' in i:
        print(i + 'make_it_sound_human')
    elif 'what_is' in i:
        print(i + 'do_not_hallucinate')
    elif 'solve' in i:
        print(i + 'make_no_mistakes')
    else:
        print(i + 'thank you')