
test_cases = int(input())

for i in range(test_cases):
    prompt = input()

    if "write_me" in prompt:
        prompt = prompt + "make_it_sound_human"
    elif "what_is" in prompt:
        prompt = prompt + "do_not_hallucinate"
    elif "solve" in prompt:
        prompt = prompt + "make_no_mistakes"
    else:
        prompt = prompt + "thank_you"

    print(prompt)
