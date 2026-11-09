import sys

def solve():
    # Read all inputs from standard input
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    for i in range(1, T + 1):
        s = input_data[i]
        
        # Check conditions and append the appropriate string
        if "write_me" in s:
            print(s + "make_it_sound_human")
        elif "what_is" in s:
            print(s + "do_not_hallucinate")
        elif "solve" in s:
            print(s + "make_no_mistakes")
        else:
            print(s + "thank_you")

if __name__ == '__main__':
    solve()