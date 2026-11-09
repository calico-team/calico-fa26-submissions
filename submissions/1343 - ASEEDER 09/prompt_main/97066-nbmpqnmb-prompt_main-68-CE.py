def main():
    s = input("")
    if s =="write_me":
        print(s+,'_'," make_it_sound_human")
    elif s =="what_is":
       print(s+,'_',"do_not_hallucinate")
    elif s =="solve":
       print(s+,'_'," make_no_mistakes")
    else:
       print(s+,'_',"thank_you")
if __name__ == "__main__":
    main()