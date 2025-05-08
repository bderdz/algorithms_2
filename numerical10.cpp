#include <iostream>
#include <cmath>

int N = 500;

//double butelka(double cm) {
//	return 10 - (cm-2) * (cm-2);
//}

double integral_volume(double h) {
	double H = h / N;
	double sum = 0;
	for (int i = 1; i < N - 1; i++) {
		sum += std::pow(butelka(i * H), 2);;
	}
	sum = std::pow(butelka(0), 2) + std::pow(butelka((N - 1) * H), 2) + 2 * sum;
	return M_PI * 0.5 * H * sum;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int x, y, z, n, counter = 0;
	double p, j;
	std::cin >> x >> y >> z >> p >> n;

	int v = x * y * z;
	double current_v = v * p;

	for (int i = 0; i < n; i++) {
		std::cin >> j;
		current_v += integral_volume(j);
		counter++;
		if (current_v >= v) break;
	}

	if (current_v >= v) std::cout << counter << "\n";
	else std::cout << "NIE\n";
	return 0;
}