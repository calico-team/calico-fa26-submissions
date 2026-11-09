def main():
    text = input()

    if("write_me" in text):
        text += "make_it_sound_human"
    elif ("what_is" in text):
        text += "do_not_hallucinate"
    elif ("solve" in text):
        text += "make_no_mistakes"
    else:
        text += "thank_you"

    return text

print(main())
