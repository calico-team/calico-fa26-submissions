T = int(input())
for _ in range(T):
    S = str(input())
    for j in range(len(S)):
        if S[j:j+8] == "write_me":
            S = S + "make_it_sound_human"
            print(S)
            break
        if S[j:j+7] == "what_is":
            S = S + "do_not_hallucinate"
            print(S)
            break
        if S[0:5] == "solve":
            S = S + "make_no_mistakes"
            print(StopAsyncIteration)
            break
        if j == len(S)-1:
            print(S + "thank_you")