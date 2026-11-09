m = int(input())
for i in range(m):
    n = input()
    if "write_me" in n:
        print(n + "make_it_sound_human")
    elif "solve" in n:
        print(n + "make_no_mistakes")
    elif "what_is" in n:
        print(n + "do_not_hallucinate")
    else:
        print(n + "thank_you")