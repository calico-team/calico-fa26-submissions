def jumla_badlo(jumla: str) -> str:
    if "write_me" in jumla:
        return jumla + "make_it_sound_human"
    if "what_is" in jumla:
        return jumla + "do_not_hallucinate"
    if "solve" in jumla:
        return jumla + "make_no_mistakes"
    return jumla + "thank_you"


def main():
    sawal_ki_tadad = int(input())
    for _ in range(sawal_ki_tadad):
        jumla = input().strip()
        print(jumla_badlo(jumla))


if __name__ == "__main__":
    main()