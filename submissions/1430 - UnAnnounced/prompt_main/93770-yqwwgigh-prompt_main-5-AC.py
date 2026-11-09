# Source: https://usaco.guide/general/io

t = int(input())
for i in range(t):
    s = input()
    ss = s
    x = False
    if 'write_me' in ss:
        s = s + 'make_it_sound_human'
        x = True
    if 'what_is' in ss:
        s = s + 'do_not_hallucinate'
        x = True
    if 'solve' in ss:
        s = s + 'make_no_mistakes'
        x = True
    if not x:
        s = s + 'thank_you'
    print(s)
