
def Problem1(s):
    if "write_me" in s:
        return s+"make_it_sound_human"
    elif "what_is" in s:
        return s+"do_not_hallucinate"
    elif "solve" in s:
        return   s+"make_no_mistakes"
    else:
        return s+"thank_you"




if __name__ == "__main__":
    t = int(input("Enter a number: "))
    for _ in range(t):
        s = input("Enter a string: ")
        Problem1(s)