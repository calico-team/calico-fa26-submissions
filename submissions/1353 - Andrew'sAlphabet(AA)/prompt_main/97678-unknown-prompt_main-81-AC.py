num = int(input())

answer = []

for i in range(num):
    n = input()
    if "write_me" in n:
        n += "make_it_sound_human"
    elif "what_is" in n:
        n += "do_not_hallucinate"
    elif "solve" in n:
        n += "make_no_mistakes"
    else:
        n += "thank_you"
    answer.append(n)
for i in answer:
    print(i)