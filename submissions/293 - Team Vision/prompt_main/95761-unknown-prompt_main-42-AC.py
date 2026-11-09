x = int(input())

for i in range(x):
    str = input()

    if "write_me" in str:
        str = str + "make_it_sound_human"
    elif "what_is" in str:
        str = str + "do_not_hallucinate"
    elif "solve" in str:
        str = str + "make_no_mistakes"
    else:
        str = str + "thank_you"

    print(str)