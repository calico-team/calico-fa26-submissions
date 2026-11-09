import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    t = int(input_data[0])
    idx = 1
    for _ in range(t):
        if idx >= len(input_data):
            break
        s = input_data[idx]
        idx += 1
        
        if "write_me" in s:
            print(s + "_make_it_sound_human")
        elif "solve" in s:
            print(s + "_make_no_mistakes")
        elif "what_is" in s:
            print(s + "_do_not_hallucinate")
        else:
            print(s + "_thank_you")

if __name__ == '__main__':
    main()