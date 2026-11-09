test_cases = int(input())

for case in range(test_cases):
    s = input().strip()

    if "write_me" in s:
        answer = s + "make_it_sound_human"
    elif "what_is" in s:
        answer = s + "do_not_hallucinate"
    elif "solve" in s:
        answer = s + "make_no_mistakes"
    else:
        answer = s + "thank_you"

    print(answer)


