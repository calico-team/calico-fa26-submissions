def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	if "write_me" in S:
		if S[-1] != '_':
			S += "_"
		S += "make_it_sound_human"
	elif "what_is" in S:
		if S[-1] != '_':
			S += "_"
		S += "do_not_hallucinate"
	elif "solve" in S:
		if S[-1] != '_':
			S += "_"
		S += "make_no_mistakes"
	else:
		if S[-1] != '_':
			S += "_"
		S += "thank_you"

	return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()