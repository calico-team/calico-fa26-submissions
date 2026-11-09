for i in range(int(input())):
    org = input()
    if "write_me" in org:
        ans = org+"make_it_sound_human"
    elif "what_is" in org:
        ans = org+"do_not_hallucinate"
    elif "solve" in org:
        ans = org+"make_no_mistakes"
    else:
        ans = org+"thank_you"
    print(ans)