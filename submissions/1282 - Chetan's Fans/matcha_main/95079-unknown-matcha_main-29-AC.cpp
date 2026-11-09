#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

struct Interval {
    int left, right;
};

struct Option {
    int prefix;
    bool full, alternate;
};

struct Choice {
    Option options[2];
    int count, pivot;

    int difference() const {
        return options[0].prefix ^ options[1].prefix;
    }
};

class Basis {
    array<int, 30> rows{}, masks{};

public:
    int freePivots = 0;

    int add(int value) {
        int mask = 0;
        while (value != 0) {
            int bit = 31 - __builtin_clz(static_cast<unsigned>(value));
            if (rows[bit] == 0) {
                int pivot = 1 << bit;
                rows[bit] = value;
                masks[bit] = mask ^ pivot;
                return pivot;
            }
            value ^= rows[bit];
            mask ^= masks[bit];
        }
        freePivots |= mask;
        return 0;
    }

    int solve(int value) const {
        int mask = 0;
        while (value != 0) {
            int bit = 31 - __builtin_clz(static_cast<unsigned>(value));
            if (rows[bit] == 0) return -1;
            value ^= rows[bit];
            mask ^= masks[bit];
        }
        return mask;
    }
};

void extend(Choice& choice, Interval interval, int parent, int size) {
    int begin = parent * (2 * size);
    int left = max(interval.left, begin);
    int right = min(interval.right, begin + 2 * size - 1);
    if (left == begin && right == begin + 2 * size - 1) return;

    int first = 2 * parent + (left >= begin + size);
    int last = 2 * parent + (right >= begin + size);
    bool leftFull = left == first * size && right >= (first + 1) * size - 1;
    bool rightFull = right == (last + 1) * size - 1 && left <= last * size;

    if (first == last) {
        choice.options[choice.count++] = {first, leftFull, false};
    } else if (leftFull) {
        choice.options[choice.count++] = {last, false, true};
    } else if (rightFull) {
        choice.options[choice.count++] = {first, false, true};
    } else {
        choice.options[choice.count++] = {first, false, false};
        choice.options[choice.count++] = {last, false, false};
    }
}

struct Flex {
    int index, option;
};

struct Feasibility {
    bool full = false;
    int flexible = 0;
    bool guaranteed = false;
    Flex firstTwo[2]{};
};

Feasibility inspect(const vector<Choice>& choices, int solution, int freePivots) {
    Feasibility result;
    if (solution < 0) return result;
    for (int i = 0; i < static_cast<int>(choices.size()); ++i) {
        const Choice& choice = choices[i];
        bool canChange = choice.count == 2 &&
                         (choice.pivot == 0 || (choice.pivot & freePivots));
        int current = (solution & choice.pivot) != 0;
        const Option& chosen = choice.options[current];
        const Option& other = choice.options[current ^ 1];
        result.full |= chosen.full || (canChange && other.full);
        bool otherFlex = canChange && other.alternate;
        if (chosen.alternate || otherFlex) {
            if (result.flexible < 2)
                result.firstTwo[result.flexible] = {i, chosen.alternate ? current : current ^ 1};
            ++result.flexible;
            result.guaranteed |= canChange ? chosen.alternate && otherFlex : chosen.alternate;
        }
    }
    return result;
}

bool canUseTwoAlternates(const vector<Choice>& choices, int target,
                         const Feasibility& options) {
    if (options.flexible < 2) return false;
    if (options.guaranteed || options.flexible >= 3) return true;

    auto [first, a] = options.firstTwo[0];
    auto [second, b] = options.firstTwo[1];
    if (a) target ^= choices[first].difference();
    if (b) target ^= choices[second].difference();

    Basis remaining;
    for (int i = 0; i < static_cast<int>(choices.size()); ++i)
        if (i != first && i != second && choices[i].count == 2)
            remaining.add(choices[i].difference());
    return remaining.solve(target) >= 0;
}

int maximize(const vector<Interval>& intervals) {
    constexpr int maximum = (1 << 30) - 1;
    for (auto [left, right] : intervals)
        if (left == 0 && right == maximum) return maximum;

    vector<Choice> choices(intervals.size());
    int prefix = 0;
    for (int bit = 29; bit >= 0; --bit) {
        int size = 1 << bit;
        Basis basis;
        int base = 0;
        for (size_t i = 0; i < intervals.size(); ++i) {
            Choice& choice = choices[i];
            choice = {};
            int first = intervals[i].left >> (bit + 1);
            int last = intervals[i].right >> (bit + 1);
            extend(choice, intervals[i], first, size);
            if (first != last) extend(choice, intervals[i], last, size);

            base ^= choice.options[0].prefix;
            if (choice.count == 2) choice.pivot = basis.add(choice.difference());
        }

        int target = (prefix << 1) | 1;
        int even = basis.solve(base ^ (target ^ 1));
        Feasibility evenOptions = inspect(choices, even, basis.freePivots);
        if (evenOptions.flexible) return target * size + size - 1;

        int odd = basis.solve(base ^ target);
        if (odd < 0) {
            prefix = target ^ 1;
            if (evenOptions.full) return prefix * size + size - 1;
        } else {
            prefix = target;
            Feasibility oddOptions = inspect(choices, odd, basis.freePivots);
            if (oddOptions.full || canUseTwoAlternates(choices, base ^ target, oddOptions))
                return prefix * size + size - 1;
        }
    }
    return prefix;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        vector<Interval> intervals(n);
        for (auto& interval : intervals) cin >> interval.left;
        for (auto& interval : intervals) cin >> interval.right;
        cout << maximize(intervals) << '\n';
    }
}
