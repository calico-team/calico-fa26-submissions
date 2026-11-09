import sys

def main():
    lines = [line.strip() for line in sys.stdin if line.strip()]
    if not lines:
        return
    t = int(lines[0])
    for s in lines[1:t+1]:
        if "write_me" in s:
            print(s + "make_it_sound_human")
        elif "what_is" in s:
            print(s + "do_not_hallucinate")
        elif "solve" in s:
            print(s + "make_no_mistakes")
        else:
            print(s + "thank_you")

if __name__ == "__main__":
    main()