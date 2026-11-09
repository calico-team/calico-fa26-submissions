def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.
	S: Original prompt
	"""

	if"write_me" in S:

		extra = "make_it_sound_human"

	elif "what_is" in S:

		extra = "do_not_hallucinate"

	elif "solve" in S:

		extra = "make_no_mistakes"

	else:

		extra = "thank_you"

	return S + extra

def main():
	
	T = int(input())
	for _ in range(T):
		S = input().strip()
		print(solve(S))

if __name__ == "__main__":
	main()