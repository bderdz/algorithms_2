#include <iostream>
#include <vector>

class RollingHash {
private:
	int base;
	int mod;
	int high_base;
	int pattern_len;
	int pattern_hash;

	void calc_high_base() {
		high_base = 1;
		for (int i = 0; i < pattern_len - 1; i++) {
			high_base = (high_base * base) % mod;
		}
	}

	void calc_pattern_hash(std::vector<int> &pattern) {
		pattern_hash = 0;
		for (int p_i: pattern) {
			pattern_hash = (base * pattern_hash + p_i) % mod;
		}
	}

public:
	RollingHash(int base, std::vector<int> &pattern, int mod) {
		this->base = base;
		this->pattern_len = pattern.size();
		this->mod = mod;

		calc_high_base();
		calc_pattern_hash(pattern);
	}

	int calc_init_window(std::vector<int> &t) {
		int t_0 = 0;
		for (int i = 0; i < pattern_len; i++) {
			t_0 = (base * t_0 + t[i]) % mod;
		}

		return t_0;
	}

	int roll(int prev_hash, int i, std::vector<int> &t) {
		int hash = (base * (prev_hash - t[i] * high_base) + t[i + pattern_len]) % mod;
		if (hash < 0) hash = hash + mod;
		return hash;
	}

	bool compare(int window_hash) {
		return window_hash == pattern_hash;
	}
};


int *find_two_occurrences(std::vector<int> &src, std::vector<int> &pattern) {
	RollingHash rh = RollingHash(101, pattern, 7);
	size_t pattern_len = pattern.size();
	size_t n = src.size();
	int *pair = new int[2]{-1};
	int counter = 0;

	int current_hash = rh.calc_init_window(src);
	for (int i = 0; i <= n - pattern_len; i++) {
		bool find = false;

		if (rh.compare(current_hash)) {
			find = true;
			for (int j = 0; j < pattern_len; j++) {
				if (pattern[j] != src[i + j]) {
					find = false;
					break;
				}
			}
		}

		if (find) {
			pair[counter] = i;
			counter++;
			if (counter == 2) break;
		}

		current_hash = rh.roll(current_hash, i, src);
	}

	return pair;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int n;
	int p_len;
	int v;
	std::vector<int> src;
	std::vector<int> pattern;

	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> v;
		src.push_back(v);
	}

	std::cin >> p_len;
	for (int i = 0; i < p_len; i++) {
		std::cin >> v;
		pattern.push_back(v);
	}

	int *pair = find_two_occurrences(src, pattern);

	while (pair[1] < n) {
		int tmp = pair[1];
		pair[1] = pair[0] + pair[1];
		pair[0] = tmp;
	}

	std::cout << pair[1] - n << "\n";
	delete pair;
	return 0;
}