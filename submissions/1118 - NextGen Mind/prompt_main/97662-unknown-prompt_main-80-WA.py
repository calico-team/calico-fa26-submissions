def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""

	res = ""
	if "write_me" in S:
		res = res + S
		res = res + "make_it_sound_human"

	if "what_is" in S:
		res = res +S
		res = res + "do_not_hallucinate"

	if "solve" in S:
		res = res + S
		res = res + "make_no_mistakes"

	else:
		res = res + S
		res = res + "thank_you"

	return "".join(res)

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()