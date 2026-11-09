def main():
    t= int(input())
    for _ in range(t):
        S =input().strip()
        if "write_me" in S:
            print(S + "make_it_sound_human")
        elif "what_is" in S:
            print(S +"do_not_hallucinate")
        elif "solve" in S:
            print(S + "make_no_mistakes")
        else:
            print(S +"thank_you")
if __name__=="__main__":
    main()