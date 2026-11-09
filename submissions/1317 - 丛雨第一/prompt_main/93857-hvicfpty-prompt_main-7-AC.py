n = int(input())
for i in range(n):
    s=input()
    s += "make_it_sound_human" if "write_me" in s else "do_not_hallucinate" if "what_is" in s else "make_no_mistakes" if "solve" in s else "thank_you"
    print(s)