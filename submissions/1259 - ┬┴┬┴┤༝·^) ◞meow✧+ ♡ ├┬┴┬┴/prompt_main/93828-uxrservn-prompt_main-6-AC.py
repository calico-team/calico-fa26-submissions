t = int(input())
for _ in range(t):
    p = input()
    if "write_me" in p:
        print(p + "make_it_sound_human")
    elif "what_is" in p:
        print(p + "do_not_hallucinate")
    elif "solve" in p:
        print(p + "make_no_mistakes")
    else:
        print(p + "thank_you")