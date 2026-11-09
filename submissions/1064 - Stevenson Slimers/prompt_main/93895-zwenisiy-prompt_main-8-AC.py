n = int(input())
for i in range(n):
    x = input()
    if "write_me" in x:
        print(x + "make_it_sound_human")
    elif "what_is" in x:
        print(x + "do_not_hallucinate")
    elif "solve" in x:
        print(x + "make_no_mistakes")
    else:
        print(x + "thank_you")
