t = int(input())
for _ in range(t):
    i = str(input())
    for j in range(len(i)):
        if i[j:j+8] == "write_me":
            i = i + "make_it_sound_human"
            print(i)
            break
        if i[j:j+7] == "what_is":
            i = i + "do_not_hallucinate"
            print(i)
            break
        if i[0:5] == "solve":
            i = i + "make_no_mistakes"
            print(i)
            break
        if j == len(i)-1:
            print(i + "thank_you")