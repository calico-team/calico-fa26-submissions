t = int(input())
for i in range(t):
    prompt = input()
    if "write_me" in prompt:
        prompt += "make_it_sound_human"
    elif "what_is" in prompt:
        prompt += "do_not_hallucinate"
    elif "solve" in prompt:
        prompt += "make_no_mistakes"
    else:
        prompt += "thank_you"
    print(prompt)
