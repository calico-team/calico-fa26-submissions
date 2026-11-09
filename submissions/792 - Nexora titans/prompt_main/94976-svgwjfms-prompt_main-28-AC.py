
Tests = int(input())

for items in range(Tests):
    String = input()

    if "write_me" in String:
        String = String + "make_it_sound_human"

    elif "what_is" in String:
        String = String + "do_not_hallucinate"

    elif "solve" in String:
        String = String + "make_no_mistakes"

    else:
        String = String + "thank_you"

    print(String)
