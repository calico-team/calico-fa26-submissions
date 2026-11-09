t = int(input())

for case in range(t):
    s = input()
    
    if "write_me" in s:
        print(s + "_make_it_sound_human")
    elif "solve" in s:
        print(s + "_make_no_mistakes")
    elif "what_is" in s:
        print(s + "_do_not_hallucinate")
    else:
        print(s + "_thank_you")