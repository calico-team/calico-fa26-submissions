def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	try:
		int(S)
		return ""
	except:
		hasAny = False
		if S.__contains__("write_me"):
			S += "make_it_sound_human"
			hasAny = True
		if S.__contains__("what_is"):
			S += "do_not_hallucinate"
			hasAny = True
		if S.__contains__("solve"):
			S += "make_no_mistakes"
			hasAny = True
		if not hasAny:
			S += "thank_you"
		return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()