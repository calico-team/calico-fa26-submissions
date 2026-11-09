import sys

def main():
    lines = sys.stdin.read().splitlines()
    if not lines:
        return
    
    t = int(lines[0].strip())
    
    for i in range(1, t + 1):
        if i >= len(lines):
            break
        s = lines[i].strip()
        
        if "write_me" in s:
            print(s + "_make_it_sound_human")
        elif "what_is" in s:
            print(s + "_do_not_hallucinate")
        elif "solve" in s:
            print(s + "_make_no_mistakes")
        else:
            print(s + "_thank_you")

if __name__ == '__main__':
    main()