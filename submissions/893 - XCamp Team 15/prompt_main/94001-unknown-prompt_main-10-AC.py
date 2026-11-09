def add(prompt):
    if "write_me" in prompt:
        print(prompt+"make_it_sound_human")
    elif "what_is" in prompt:
        print(prompt+"do_not_hallucinate")
    elif "solve" in prompt:
        print(prompt+"make_no_mistakes")
    else:
        print(prompt+"thank_you")



def start():
    t=int(input())
    for i in range(t):
        ask=input()
        add(ask)
start()