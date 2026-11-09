for _ in range(int(input())):
    l = input()
    if "write_me" in l:
        print(l + "make_it_sound_human")
        continue
    if "what_is" in l:
        print(l + "do_not_hallucinate")
        continue
    if "solve" in l:
        print(l + "make_no_mistakes")
        continue
    print(l + "thank_you")
