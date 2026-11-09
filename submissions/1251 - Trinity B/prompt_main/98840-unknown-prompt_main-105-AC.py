def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	if "write_me" in S:
		string = S + "make_it_sound_human"
	elif "what_is" in S:
		string = S + "do_not_hallucinate"
	elif "solve" in S:
		string = S + "make_no_mistakes"
	else:
		string = S + "thank_you"

	return string

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()