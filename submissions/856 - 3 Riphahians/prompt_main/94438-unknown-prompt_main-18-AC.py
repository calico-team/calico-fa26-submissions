quantity = int(input())
for _ in range(quantity):
    str = input()
    if "write_me" in str:
        str += "make_it_sound_human"
    elif "what_is" in str:
        str += "do_not_hallucinate"
    elif "solve" in str:
        str += "make_no_mistakes"
    else:
        str += "thank_you"
    print(str)
