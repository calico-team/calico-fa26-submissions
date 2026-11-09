def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	return ""

def main():
	T = int(input())
	for _ in range(T):
		S = input()

                if 'write_me' in s:
                    print(s + 'make_it_sound_human')
                elif 'what_is' in s:
                    print(s + 'do_not_hallucinate')
                elif 'solve' in s:
                    print(s + 'make_no_mistakes')
                else:
                    print(s + 'thank you')
		print(solve(S))

if __name__ == "__main__":
	main()
