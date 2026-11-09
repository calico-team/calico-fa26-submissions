t = int(input())
for i in range(t):
    s = input()
    done = False
    for a in range(len(s) - 7):
        if s[a:a+8] == "write_me":
            print(s + "make_it_sound_human")
            done = True
            break
    if not done:
        for a in range(len(s) - 6):
            if s[a:a+7] == "what_is":
                print(s + "do_not_hallucinate")
                done = True
                break
    if not done:
        for a in range(len(s) - 4):
            if s[a:a+5] == "solve":
                print(s + "make_no_mistakes")
                done = True
                break
    if not done:
        print(s + "thank_you")

    
