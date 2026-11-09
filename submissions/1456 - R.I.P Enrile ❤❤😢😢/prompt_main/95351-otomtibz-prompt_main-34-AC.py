def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	a=False
	b=False
	c=False
	if "write_me" in S:
		a=True
	if "what_is" in S:
		b=True
	if "solve" in S:
		c=True
	if (not a) and (not b) and (not c):
		return S + "thank_you"
	else:
		if a:
			S+="make_it_sound_human"
		if b:
			S+="do_not_hallucinate"
		if c:
			S+="make_no_mistakes"
		return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()