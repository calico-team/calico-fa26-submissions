def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	if "write_me" in S:
		S = S + "make_it_sound_human"
	if "what_is" in S:
		S = S + "do_not_hallucinate"
	if "solve" in S:
		S = S + "make_no_mistakes"
	if "write_me" not in S and "what_is" not in S and "solve" not in S:
		S = S + "thank_you"
	return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()