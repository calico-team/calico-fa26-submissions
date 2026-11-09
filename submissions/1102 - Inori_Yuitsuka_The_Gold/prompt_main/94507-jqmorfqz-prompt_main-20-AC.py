

i=int(input())

for j in range(i):
    str=input();

    if "write_me" in str:
        print(str+"make_it_sound_human")

    elif "what_is" in str:
        print(str+"do_not_hallucinate")

    elif "solve" in str:
        print(str+"make_no_mistakes")

    else:
        print(str+"thank_you")

    