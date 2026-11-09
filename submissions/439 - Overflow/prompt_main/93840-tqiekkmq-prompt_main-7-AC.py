SUFFIXES = [
    ("write_me", "make_it_sound_human"),
    ("what_is", "do_not_hallucinate"),
    ("solve", "make_no_mistakes"),
]

def modified_prompt(prompt):
    for pattern, suffix in SUFFIXES:
        if pattern in prompt:
            return prompt + suffix
    return prompt + "thank_you"

for _ in range(int(input())):
    print(modified_prompt(input().strip()))