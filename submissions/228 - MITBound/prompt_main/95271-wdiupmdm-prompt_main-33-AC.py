def solve(S: str) -> str:
    check = 0
    S = S.strip()
    if "write_me" in S:
        S = S + "make_it_sound_human"
        check += 1
    if "what_is" in S:
        S = S + "do_not_hallucinate"
        check += 1
    if "solve" in S:
        S = S + "make_no_mistakes"
        check += 1
    if check == 0:
        S = S + "thank_you"
    return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()

