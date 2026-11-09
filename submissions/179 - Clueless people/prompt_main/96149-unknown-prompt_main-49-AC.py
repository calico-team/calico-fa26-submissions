def solve(S: str) -> str:
	for i in range(len(S)):
		if S[i:i+8] == 'write_me':
			S+= "make_it_sound_human"
			return S
		elif S[i:i+7] == 'what_is':
			S+= "do_not_hallucinate"
			return S
		elif S[i:i+5] == 'solve':
			S+= "make_no_mistakes"
			return S
	S += 'thank_you'
			
	return S


	# """
	# Output the result of adding a certain string to the end of a prompt.

	# S: Original prompt
	# """
	# return ""

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()