t=int(input())
def case(i):
    if 'write_me' in i:
        i+='make_it_sound_human'
    elif 'what_is' in i:
            i+='do_not_hallucinate'
    elif 'solve' in i:
            i+='make_no_mistakes'
    else:
          i+='thank_you'
    return i
for _ in range(t):
    print(case(input()))