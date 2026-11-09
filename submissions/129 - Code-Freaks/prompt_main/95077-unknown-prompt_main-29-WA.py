def solve(S):

    if "write_me" in S:
        temp = S + "make_it_sound_human"
        return temp
    elif "what_is" in S:
	    temp = S + "do_not_hallucinate"
	    return temp
    elif "solve" in S:
	    temp = S + "make_no_mistakes"
	    return temp
    return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()