t=int(input())
s=""
t1="write_me"
t2="what_is"
t3="solve"
t1s="make_it_sound_human"
t2s="do_not_hallucinate"
t3s="make_no_mistakes"
t4s="thank_you"

ans=[]

for i in range(t):
    s=input()
    if t1 in s:
        s+=t1s
    elif t2 in s:
        s+=t2s
    elif t3 in s:
        s+=t3s
    else:
        s+=t4s
    ans.append(s)
for i in range(len(ans)):
    print(ans[i])