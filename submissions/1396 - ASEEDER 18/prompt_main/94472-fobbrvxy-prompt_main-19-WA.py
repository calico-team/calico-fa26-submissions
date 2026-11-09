def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	list = S.strip().split("_")
	flag = False
	for i in range(len(list)-1):
		if  list[i] +list[i+1]== "writeme":
			list[len(list)-1]="make_it_sound_human"
			flag = True
		if list[i] +list[i+1]== "whatis":
			list[len(list)-1]="do_not_hallucinate"
			flag = True
		if list[i] == "solve" or list[i+1] == "solve":
			list[len(list)-1]="make_no_mistakes"
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