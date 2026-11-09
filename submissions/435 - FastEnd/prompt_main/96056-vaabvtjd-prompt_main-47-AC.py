def solve(S: str) -> str:
    """
    Output the result of adding a certain string to the end of a prompt.

    S: Original prompt
    """
    prompt_mapping = {
        "write_me": "make_it_sound_human",
        "what_is": "do_not_hallucinate",
        "solve": "make_no_mistakes",
    }
    match_found = False
    matched_str = ""
    for key in prompt_mapping:
        if key in S:
            matched_str = S+prompt_mapping[key]
            match_found = True
            break
    if not match_found:
        matched_str = S+"thank_you"
    return matched_str


def main():
    T = int(input())
    for _ in range(T):
        S = input()
        print(solve(S))


if __name__ == "__main__":
    main()
