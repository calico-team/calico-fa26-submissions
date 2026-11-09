# a = "solve_all_of_the_rank_4_problems_"

a = input()
a = a.split("_")

for i in a:
    i = i.lower()
    if i == "write":
        a.append("make_it_sound_human")
        break

    elif i == "what":
        a.append("do_not_hallucinate")
        break

    elif i == "solve":
        a.append("make_no_mistakes")
        break

    else:
        a.append("thank_you")
        break

print("_".join(a))