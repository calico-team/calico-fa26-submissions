def main():
    text = input()

    if("write_me" in text):
        text += "_make_it_sound_human"
    elif ("what_is" in text):
        text += "_do_not_hallucinate"
    elif ("solve" in text):
        text += "_make_no_mistakes"
    else:
        text += "_thank_you"

    return text

n = int(input())

for i in range(n):
    print(main())
