


def solve(S: str) -> str:
    if 'write_me' in x:
        x = x + ('make_it_sound_human')
    elif 'what_is' in x:
        x = x +('do_not_hallucinate')
    elif 'solve' in x:
        x = x + ('make_no_mistakes')
    else:
        x = x + ('thank_you')
    return x

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()






