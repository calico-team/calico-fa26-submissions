def solution():
    test_cases_input=int(input())
    for b in range(test_cases_input):
        input_prompt=input()
        if "write_me" in input_prompt:
            input_prompt += "make_it_sound_human"
        elif "what_is" in input_prompt:
            input_prompt += "do_not_hallucinate"
        elif "solve" in input_prompt:
            input_prompt += "make_no_mistakes"
        else:
            input_prompt += "thank_you"
        print(input_prompt)
solution()