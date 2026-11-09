test_cases= int(input())
for i in range(test_cases):
    input_str = input()
    if "write_me" in input_str:
        print(input_str + "make_it_sound_human")
    elif "what_is" in input_str:
        print(input_str+ "do_not_hallucinate")
    elif "solve" in input_str:
        print(input_str + "make_no_mistakes")
    else:
        print(input_str + "thank_you")