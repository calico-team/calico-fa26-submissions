def solve(S):
    temp = ""
    if "write_me" in S:
        temp = S + "make_it_sound_human"
    elif "what_is" in S:
	    temp = S + "do_not_hallucinate"
    elif "solve" in S:
	    temp = S + "make_no_mistakes"
    else:
        temp = S + "make_no_mistakes"
    return temp

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()