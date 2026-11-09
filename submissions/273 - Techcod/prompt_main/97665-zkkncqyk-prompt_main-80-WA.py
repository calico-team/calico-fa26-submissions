def main():
    t= int(input())
    for _ in range(t):
        S =input().strip()
        if "write_me" in S:
            print(S + "_make_it_sound_human")
        elif "what_is" in S:
            print(S +"_do_not_hallucinate")
        elif "solve" in S:
            print(S + "_make_no_mistakes")
        else:
            print(S +"_thank_you")
if __name__=="__main__":
    main()