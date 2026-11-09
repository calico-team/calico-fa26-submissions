a = int(input())
for i in range(a):
    s = input()
    if "write_me" in s:
        print(s + "make_it_sound_human")
    elif "what_is" in s:
        print(s + "do_not_hallucinate")
    elif "solve" in s:
        print(s + "make_no_mistakes")
    else:
        print(s + "thank_you")
