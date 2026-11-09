
text = int(input("Enter text"))

for i in range(text):
    stri = input()

    if "write_me" in stri:
        s += "make_it_sound_human"
    elif "what_is" in stri:
        stri += "do_not_hallucinate"
    elif "solve" in stri:
        stri += "make_no_mistakes"
    else:
        stri += "thank_you"

    print(stri)
