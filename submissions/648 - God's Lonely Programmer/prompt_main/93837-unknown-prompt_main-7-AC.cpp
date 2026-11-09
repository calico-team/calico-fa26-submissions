#include <bits/stdc++.h>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);

	int T; std::cin >> T;
	while (T--) {
		std::string S; std::cin >> S;
		if (S.find("write_me") != std::string::npos) S += "make_it_sound_human";
		else if (S.find("what_is") != std::string::npos) S += "do_not_hallucinate";
		else if (S.find("solve") != std::string::npos) S += "make_no_mistakes";
		else S += "thank_you";
		std::cout << S << '\n';
	}

	return 0;
}
