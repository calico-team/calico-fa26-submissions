def solve(S: str) -> str:
	if "write me" in S:
		S += "make_it_sound_human"
	if "what_is" in S:
		S += "do_not_hallucinate"
	if "solve" in S:
		S += "make_no_mistakes"
	else: 
		S += "thank_you"
	return S
def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()