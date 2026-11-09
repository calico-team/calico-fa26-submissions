for _ in range(int(input())):
    x = input()
    if "write_me" in x:
        print(x + "make_it_sound_human")
        continue
    if "what_is" in x:
        print(x + "do_not_hallucinate")
        continue
    if "solve" in x:
        print(x + "make_no_mistakes")
        continue
    print(x + "thank_you")