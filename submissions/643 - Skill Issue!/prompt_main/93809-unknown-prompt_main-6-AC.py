for i in range(int(input())):
    a = input()

    if("write_me" in a):
        print(a+"make_it_sound_human")
    elif "solve" in a:
        print(a+"make_no_mistakes")
    elif "what_is" in a:
        print(a+"do_not_hallucinate")
    else:
        print(a+"thank_you")