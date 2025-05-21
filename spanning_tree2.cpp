#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

struct Edge {
	int v;
	double prob;

	bool operator<(const Edge &edge) const {
		return prob < edge.prob;
	}
};

double survive_probability(std::vector<std::vector<Edge>> &graph, int v) {
	std::vector<bool> visited(v, false);
	std::priority_queue<Edge> pq;
	double probability = 1.0;
	int counter = 0;

	pq.push({0, 1.0});

	while (counter <= v - 1 && !pq.empty()) {
		Edge current = pq.top();
		pq.pop();

		if (!visited[current.v]) {
			probability *= current.prob;

			for (Edge neighbor: graph[current.v]) {
				pq.push(neighbor);
			}

			visited[current.v] = true;
			counter++;
		}
	}

	return probability;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int n, m;

	std::cin >> n >> m;

	std::vector<std::vector<Edge>> graph(n);

	for (int i = 0; i < m; i++) {
		double prob;
		int a, b;
		std::cin >> a >> b >> prob;

		graph[a].push_back({b, prob});
		graph[b].push_back({a, prob});
	}

	double probability = survive_probability(graph, n);

	std::cout << std::fixed << std::setprecision(5) << probability << "\n";

	return 0;
}