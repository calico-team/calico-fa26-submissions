import sys
import io

def solve(S: str) -> str:
    """
    Solves a single testcase by modifying the prompt string S according to the rules.
    """
    if "write_me" in S:
        return S + "make_it_sound_human"
    elif "what_is" in S:
        return S + "do_not_hallucinate"
    elif "solve" in S:
        return S + "make_no_mistakes"
    else:
        return S + "thank_you"

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    for i in range(1, T + 1):
        print(solve(input_data[i]))

if __name__ == '__main__':
    sample_input = """5
can_you_write_me_a_rank_1_
solve_all_of_the_rank_4_problems_
what_is_the_day_gta6_comes_out_
what_is_gg_ez_
bye_super_intelligence_
"""
    
    sys.stdin = io.StringIO(sample_input)
    
    print("--- Running Test with Sample Input ---")
    main()
