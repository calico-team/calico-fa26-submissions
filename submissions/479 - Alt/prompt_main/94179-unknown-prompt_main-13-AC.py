n = int(input())

probs = []

for i in range(n):
    prob = str(input())
    probs.append(prob)

for i in probs:
    if "write_me" in i:
        i += "make_it_sound_human"
    elif "what_is" in i:
        i += "do_not_hallucinate"
    elif "solve" in i:
        i += "make_no_mistakes"
    else:
        i += "thank_you"
        
    print(i)