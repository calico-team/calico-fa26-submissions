n = int(input(''))
s = []
for i in range(n):
    st = input('')
    s.append(st)
for a in range(n):
    if 'write_me' in s[a]:
        s[a] = s[a] + 'make_it_sound_human'
    elif 'what_is' in s[a]:
        s[a] = s[a] + 'do_not_hallucinate'
    elif 'solve' in s[a]:
        s[a] = s[a] + 'make_no_mistakes'
    else:
        s[a] = s[a] + 'thank_you'
for k in s:
    print(k)