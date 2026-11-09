t=int(input())
for i in range(t):
    s=input()
    if 'write_me' in s:
        s=s+'make_it_sound_human'
    elif 'what_is' in s:
        s=s+'do_not_hallucinate'
    elif 'solve' in s:
        s=s+'make_no_mistakes'
    else:
        s=s+'thank_you'
    print(s)