def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	list = S.split()
	flag = False
	for i in list:
		if i == "write":
			list.append("make_it_sound_human")
			flag = True
		if i == "what":
			list.append("do_not_hallucinate")
			flag = True
		if i == "solve":
			list.append("make_no_mistakes")
			flag = True
	if not flag:
		list.append("thank_you")

	return "_".join(list)

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()