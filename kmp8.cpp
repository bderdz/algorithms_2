#include <iostream>
#include <string>
#include <vector>

void longest_prefix_suffix(std::string &pattern, std::vector<int> &lps) {
	int j = 0;
	int i = 1;

	while (i < pattern.length()) {
		if (pattern[i] == pattern[j]) {
			j++;
			lps[i] = j;
		} else {
			if (j != 0) {
				j = lps[j - 1];
				continue;
			}

			lps[i] = 0;
		}
		i++;
	}
}

char format_input(char &c) {
	if (c >= 'a' && c <= 'z') return 'a';
	else if (c >= 'A' && c <= 'Z') return 'A';
	else if (c >= '0' && c <= '9') return '0';
	else if (c == '?' || c == '!' || c == ',' || c == '.' || c == ':' || c == ';' || c == '-') return '.';
	else return ' ';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	std::string pattern;
	std::getline(std::cin, pattern);

	std::vector<int> lps(pattern.length(), 0);
	longest_prefix_suffix(pattern, lps);

	int j = 0;
	size_t p_len = pattern.size();
	char c;
	while (std::cin.get(c)) {
		if (c == '\n') {
			std::cout << "N\n";
			break;
		}

		c = format_input(c);
		while (j > 0 && pattern[j] != c) j = lps[j - 1];

		if (pattern[j] == c) {
			j++;
		}

		if (j == p_len) {
			std::cout << "T\n";
			break;
		}
	}

	return 0;
}