def solve(S: str) -> str:

	if "write_me" in S:
		r = S + "make_it_sound_human"
	elif "what_is" in S:
		r = S + "do_not_hallucinate"
	elif "solve" in S:
		r = S + "make_no_mistakes"
	else:
		r = S + "thank_you"

	return r

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()