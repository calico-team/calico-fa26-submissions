string_count = int(input())
outputs = []
for i in range(string_count):
    string_input = input()
    if "write_me" in string_input:
        string_output = string_input + "make_it_sound_human"
    elif "what_is" in string_input:
        string_output = string_input + "do_not_hallucinate"
    elif "solve" in string_input:
        string_output = string_input + "make_no_mistakes"
    else:
        string_output = string_input + "thank_you"
    outputs.append(string_output)
for output in outputs:
    print(output)