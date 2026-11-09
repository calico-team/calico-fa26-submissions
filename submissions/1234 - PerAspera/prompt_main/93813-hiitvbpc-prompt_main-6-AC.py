n = int(input())
for _ in range(n):
    sen = input()
    if "write_me" in sen:
        print(sen + "make_it_sound_human")
    elif "what_is" in sen:
        print(sen + "do_not_hallucinate")
    elif "solve" in sen:
        print(sen + "make_no_mistakes")
    else:
        print(sen + "thank_you")
