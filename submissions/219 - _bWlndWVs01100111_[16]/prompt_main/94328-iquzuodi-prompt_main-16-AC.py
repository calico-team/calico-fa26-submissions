a = int(input())
for i in range(a):
    l = ['write_me', 'what_is', 'solve']
    b = input()
    if 'write_me' in b:
        b += 'make_it_sound_human'
    elif 'what_is' in b:
        b += 'do_not_hallucinate'
    elif 'solve' in b:
        b += 'make_no_mistakes'
    else:
        b += 'thank_you'
    print(b)
        
            