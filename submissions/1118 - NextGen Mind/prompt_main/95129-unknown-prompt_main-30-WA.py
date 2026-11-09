def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""

	res = []
	if "write_me" in S:
		res.append(S)
		res.append("make_it_sound_human")

	if "what_is" in S:
		res.append(S)
		res.append("do_not_hallucinate")

	if "solve" in S:
		res.append(S)
		res.append("make_no_mistakes")

	else:
		res.append(S)
		res.append("thank_you")

	return "".join(res)

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()