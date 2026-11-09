import sys


def smoke_de_sakta_hai(waqt_ki_list, recharge_waqt):
    charges = 2
    agla_charge_waqt = 0  # jab agla charge wapas milega

    for waqt in waqt_ki_list:
        # pehle recharge process karo (ek waqt mein sirf ek charge recharge hota hai)
        while charges < 2 and agla_charge_waqt <= waqt:
            charges += 1
            if charges < 2:
                agla_charge_waqt += recharge_waqt

        if charges == 0:
            return False

        if charges == 2:
            # dono charges full thay, ab recharge abhi shuru hoga
            agla_charge_waqt = waqt + recharge_waqt
        charges -= 1

    return True


def main():
    data = sys.stdin.buffer.read().split()
    index = 0
    sawal_ki_tadad = int(data[index]); index += 1
    jawab = []
    for _ in range(sawal_ki_tadad):
        n = int(data[index]); recharge_waqt = int(data[index + 1]); index += 2
        waqt_ki_list = list(map(int, data[index:index + n])); index += n
        jawab.append("YES" if smoke_de_sakta_hai(waqt_ki_list, recharge_waqt) else "NO")
    print("\n".join(jawab))


if __name__ == "__main__":
    main()