import sys
import io

SAMPLE = """5
can_you_write_me_a_rank_1_
solve_all_of_the_rank_4_problems_
what_is_the_day_gta6_comes_out_
what_is_gg_ez_
bye_super_intelligence_
"""


if len(sys.argv) > 1 and sys.argv[1] == "test":
    readline = io.BytesIO(SAMPLE.encode()).readline
else:
    readline = sys.stdin.buffer.readline

t = int(readline())
out = []
for _ in range(t):
    s = readline().decode().strip()
    if "write_me" in s:
        s += "make_it_sound_human"
    elif "what_is" in s:
        s += "do_not_hallucinate"
    elif "solve" in s:
        s += "make_no_mistakes"
    else:
        s += "thank_you"
    out.append(s)

print("\n".join(out))