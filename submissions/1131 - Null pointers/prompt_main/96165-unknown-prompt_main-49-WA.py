def solve(S):
    if "write_me" in S:
        S += "make_it_sound_human"
    elif "what_is" in S:
	    S += "do_not_hallucinate"
    elif "solve" in S:
	    S += "make_no_mistakes"
    else:
        S += "make_no_mistakes"
    return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()