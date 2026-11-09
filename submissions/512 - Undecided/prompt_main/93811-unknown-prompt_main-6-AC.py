n=int(input())
for i in range(n):
    x = input()
    if "write_me" in x:
        x+="make_it_sound_human"
    elif "what_is" in x:
        x+="do_not_hallucinate"
    elif "solve" in x:
        x+="make_no_mistakes"
    else:
        x+="thank_you"
    print(x)