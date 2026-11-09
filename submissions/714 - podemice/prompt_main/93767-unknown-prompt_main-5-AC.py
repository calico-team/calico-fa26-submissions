N = int(input())

for _ in range(N):
    curr = input()
    if 'write_me' in curr:
        print(curr + "make_it_sound_human")
    elif 'what_is' in curr:
        print(curr+"do_not_hallucinate")
    elif 'solve' in curr:
        print(curr + 'make_no_mistakes')
    else:
        print(curr + 'thank_you')