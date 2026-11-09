
n = int(input())

l = []

for i in range(n):
    p = input()

    if "write_me" in p:
        #print(p+"make_it_sound_human")
        l.append(p+"make_it_sound_human")
    if "what_is" in p:
        #print(p+"do_not_hallucinate ")
        l.append(p+"do_not_hallucinate ")
    if "solve" in p:
        #print(p+"make_no_mistakes")
        l.append(p+"make_no_mistakes")

print('\n'.join(l))