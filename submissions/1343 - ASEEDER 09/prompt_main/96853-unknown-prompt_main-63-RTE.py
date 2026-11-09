def main():
    s = input("enter a string")
    if s.sort() =="write_me":
        print(s+" make_it_sound_human")
    elif s.sort()  =="what_is":
       print(s+"do_not_hallucinate")
    elif s.sort()  =="solve":
       print(s+" make_no_mistakes")
    else:
       print("thank_you")
if __name__ == "__main__":
    main()