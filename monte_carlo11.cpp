#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

typedef unsigned int uint;
int SIM_N = 50000;

int Loptr(int HH, int mm) {
	if (HH >= 8 && HH < 15) return 0;
	else if (HH >= 15 && HH < 22) return 1;
	return 2;
}

int to_minutes(uint hh, uint mm) {
	return hh * 60 + mm;
}

double monte_carlo_prob(uint start_min, uint end_min, uint target, int sim_n) {
	int hits = 0;
	uint range = end_min - start_min;

	for (int i = 0; i < sim_n; i++) {
		int rand_minutes = start_min + std::rand() % (range + 1);
		if (Loptr(rand_minutes / 60, rand_minutes % 60) == target) hits++;
	}
	return hits * 1.0 / sim_n;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);
	srand(time(0));
	char c;
	uint hh, mm;
	uint target;
	uint minutes[2] = {0};

	for (int i = 0; i < 2; i++) {
		std::cin >> hh >> c >> mm;
		minutes[i] = to_minutes(hh, mm);
	}
	std::cin >> target;

	double result = monte_carlo_prob(minutes[0], minutes[1], target, SIM_N);
	std::cout << std::fixed << std::setprecision(2) << result << "\n";
	return 0;
}