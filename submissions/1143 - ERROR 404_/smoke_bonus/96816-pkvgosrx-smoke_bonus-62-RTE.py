import sys

def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    nums = list(map(int, data))
    idx = 0
    t = nums[idx]
    idx += 1
    out = []
    for _ in range(t):
        if idx + 1 >= len(nums):
            break
        n = nums[idx]
        R = nums[idx + 1]
        idx += 2
        # pending recharge times, at most 2, kept sorted
        p0 = -1
        p1 = -1
        charges = 2
        ok = True
        for _ in range(n):
            if idx >= len(nums):
                break
            a = nums[idx]
            idx += 1
            # process recharges <= a
            if p0 != -1 and p0 <= a:
                charges += 1
                p0 = p1
                p1 = -1
            if p0 != -1 and p0 <= a:
                charges += 1
                p0 = p1
                p1 = -1
            if charges == 0:
                ok = False
                # still need to skip remaining A values (already counted via loop)
                # continue consuming them without logic
                # we already are in loop, just keep skipping
                # to keep idx correct, the for loop will consume rest
                # set a flag and keep looping with no-op
                # we do it by continuing but not using charges
                # To avoid breaking idx, just continue
                # Mark charges as 0 and skip rest via dummy
                # Simplest: consume remaining and break
                # remaining iterations are handled by loop, so set ok=False and keep
                # we need to not append again, so use a separate skip
                # consume rest of this test case:
                # (idx already points after current a, need to skip n-1 - processed)
                # Instead, break out and adjust idx manually is complex,
                # so just continue with a flag that forces ok=False
                # and do not use charges logic
                # We handle by setting charges = 0 and p0/p1 = large
                # and letting loop run but it will stay False
                # To avoid infinite, we set a marker:
                # Use a dummy loop for remaining:
                # (we are inside for, so we can just continue; the next iterations
                #  will also hit charges==0 and stay False, but they will
                #  try to process recharges - that is fine, they will still
                #  consume input correctly)
                # So just continue
                continue
            # use one charge
            charges -= 1
            if p0 == -1:
                finish = a + R
                p0 = finish
            else:
                # p0 is the pending one, new one waits for it
                finish = p0 + R
                # p0 stays, p1 = finish (keep sorted: p0 < finish)
                p1 = finish
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()