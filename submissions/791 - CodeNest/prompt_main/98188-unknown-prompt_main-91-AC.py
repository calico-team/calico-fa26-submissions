

def modify_prompt(prompt):
    if "write_me" in prompt:
        return prompt + "make_it_sound_human"
    if "what_is" in prompt:
        return prompt + "do_not_hallucinate"
    if "solve" in prompt:
        return prompt + "make_no_mistakes"

    return prompt + "thank_you"


def main():
    test_case = int(input())

    for _ in range(test_case):
        prompt = input().strip()
        print(modify_prompt(prompt))


if __name__ == "__main__":
    main()
