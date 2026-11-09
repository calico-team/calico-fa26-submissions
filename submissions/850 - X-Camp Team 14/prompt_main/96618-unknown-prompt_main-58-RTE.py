import sys

def main():
    lines = sys.stdin.read().splitlines()
    if not lines:
        return
    
    t = int(lines[0].strip())
    
    for i in range(1, t + 1):
        if i >= len(lines):
            break
        s = lines[i]
        
        if "write_me" in s:
            s = s.append("make_it_sound_human")
            print(s)
        elif "what_is" in s:
            s = s.append("do_not_hallucinate")
            print(s)
        elif "solve" in s:
            s = s.append("make_no_mistakes")
            print(s)
        else:
            s = s.append("thank_you")
            print(s)

if __name__ == '__main__':
    main()