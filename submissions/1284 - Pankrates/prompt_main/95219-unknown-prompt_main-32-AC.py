def solve(s: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""

	if "write_me" in s:
		return s + "make_it_sound_human"
	elif "what_is" in s:
		return s + "do_not_hallucinate"
	elif "solve" in s:
		return s + "make_no_mistakes"
	return s + "thank_you"


def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()