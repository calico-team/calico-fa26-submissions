import sys

def main():
    lines = sys.stdin.read().splitlines()
    if not lines:
        return
    
    # Clean up empty lines
    lines = [line.strip() for line in lines if line.strip()]
    if not lines:
        return
    
    # Check if the first line is an integer (T) or a prompt string
    try:
        T = int(lines[0])
        # If it's an integer, the test cases start from index 1 up to T
        test_cases = lines[1:1+T]
    except ValueError:
        # If it's NOT an integer, then every single line is a test case!
        test_cases = lines
    
    results = []
    for s in test_cases:
        if "write_me" in s:
            results.append(s + "make_it_sound_human")
        elif "what_is" in s:
            results.append(s + "do_not_hallucinate")
        elif "solve" in s:
            results.append(s + "make_no_mistakes")
        else:
            results.append(s + "thank_you")
            
    sys.stdout.write('\n'.join(results) + '\n')

if __name__ == '__main__':
    main()