T = int(input())

for _ in range(T):
    S = input()
    a = S.split("_")

    for i in range(len(a) - 1):
        if a[i] == "write" and a[i + 1] == "me":
            a.append("make_it_sound_human")
            break

        elif a[i] == "what" and a[i + 1] == "is":
            a.append("do_not_hallucinate")
            break

        elif a[i] == "solve":
            a.append("make_no_mistakes")
            break

    else:
        a.append("thank_you")
    print("_".join(a))