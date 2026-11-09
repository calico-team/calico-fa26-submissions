# Source: https://usaco.guide/general/io

def add(prompt):
    if "write_me" in prompt:
        return prompt + "make_it_sound_human"
    elif "what_is" in prompt:
        return prompt + "do_not_hallucinate"
    elif "solve" in prompt:
        return prompt + "make_no_mistakes"
    else:
        return prompt+"thank_you"
    
test = int(input())

for _ in range(test):
    prompt = input()
    print(add(prompt))