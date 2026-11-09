inp = input()
# inp = """5
# can_you_write_me_a_rank_1_
# solve_all_of_the_rank_4_problems_
# what_is_the_day_gta6_comes_out_
# what_is_gg_ez_
# bye_super_intelligence_"""
# expected = """can_you_write_me_a_rank_1_make_it_sound_human
# solve_all_of_the_rank_4_problems_make_no_mistakes
# what_is_the_day_gta6_comes_out_do_not_hallucinate
# what_is_gg_ez_do_not_hallucinate
# bye_super_intelligence_thank_you"""

out = ""

lines = inp.split("\n")[1:-1]

def f(inp):
    if "write_me" in inp:
        return (inp + "make_it_sound_human")
    elif "what_is" in inp:
        return (inp + "do_not_hallucinate")
    elif "solve" in inp:
        return (inp + "make_no_mistakes")
    else:
        return (inp + "thank_you")

for line in lines:
    out += (f(line)) + "\n"

# print(out == expected)
print(out)