import sys
def solve():
    input_data = sys.stdin.read().splitlines()
    if not input_data:
        return
    
    T = int(input_data[0].strip())
    results = []
    
    for i in range(1, T +1):
        if i >= len(input_data):
            break
        s = input_data[i].strip()
        
        if "write_me" in s:
            results.append(s + "make_it_sound_human")
        elif "what_is" in s:
            results.append(s + "do_not_hallucinate")
        elif "solve" in s:
            results.append(s + "make_no_mistakes")
        else:
            results.append(s + "thank_you")
            
    print('\n'.join(results))
    
if __name__ == '__main__':
    solve()