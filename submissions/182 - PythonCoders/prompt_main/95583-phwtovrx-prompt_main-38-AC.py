i=int(input())
for n in range(0,i):
    b=0
    s=input()
    prompt=[]
    prompt.append(s)
    if 'write_me' in s:
        prompt.append('make_it_sound_human')
        b+=1
    if 'what_is' in s:
        prompt.append('do_not_hallucinate')
        b+=1
    if 'solve' in s:
        prompt.append('make_no_mistakes')
        b+=1
    if not b>=1:
        prompt.append('thank_you')
    a="".join(prompt)
    print(a)
    b=0
