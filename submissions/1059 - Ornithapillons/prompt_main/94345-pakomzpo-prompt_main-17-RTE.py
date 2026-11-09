def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""


	strIn =  [
		"write_me",
		"what_is",
		"solve"
	]

	strOut = [
		"make_it_sound_human",
		"do_not_hallucinate",
		"make_no_mistakes"
	]

	for i in range(3):
		if strIn[i] in str:
			str = str + strOut[i]


	return str

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()