import sys


def transform(text):
    if "write_me" in text:
        suffix = "make_it_sound_human"
    elif "what_is" in text:
        suffix = "do_not_hallucinate"
    elif "solve" in text:
        suffix = "make_no_mistakes"
    else:
        suffix = "thank_you"
    return text + suffix


def run():
    tokens = sys.stdin.read().split()
    cases = int(tokens[0])
    answers = []
    for k in range(1, cases + 1):
        answers.append(transform(tokens[k]))
    sys.stdout.write("\n".join(answers) + "\n")


run()
