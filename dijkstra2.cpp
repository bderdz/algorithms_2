//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <queue>
//#include <limits.h>
//
//struct Point {
//	int idx;
//	int x, y;
//
//	Point(int idx, int x, int y) : idx(idx), x(x), y(y) {}
//};
//
//struct Node {
//	int idx;
//	int distance;
//
//	Node(int idx, int distance) : idx(idx), distance(distance) {}
//
//	bool operator<(const Node &node) const {
//		return distance > node.distance;
//	}
//};
//
//// DEBUG Lista sąsiadów
//void print_graph(std::vector<std::vector<Node>> graph) {
//	std::cout << "-----\n";
//
//	for (int i = 0; i < graph.size(); i++) {
//		if (graph[i].empty()) {
//			std::cout << "--";
//		} else {
//			for (Node node: graph[i]) {
//				std::cout << "(" << node.idx << ", " << node.distance << "), ";
//			}
//		}
//
//		std::cout << "\n";
//	}
//}
//
//void push_edge(int a, int b, int d, std::vector<std::vector<Node>> &graph) {
//	graph[a].push_back(Node(b, d));
//	graph[b].push_back(Node(a, d));
//}
//
///*
// * inny sposób
//int distance_x = src[i + 1].x - src[i].x;
//int distance_y = src[i + 1].y - src[i].y;
//min(distance_x, distance_y)
// */
//
//std::vector<std::vector<Node>> reduce_graph(std::vector<Point> src, int n) {
//	std::vector<std::vector<Node>> graph_x(n);
//	std::vector<std::vector<Node>> graph_y(n);
//
//	std::sort(src.begin(), src.end(), [](Point &a, Point &b) { return a.x < b.x; });
//
//	for (int i = 0; i < n - 1; i++) {
//		int distance = src[i + 1].x - src[i].x;
//		push_edge(src[i].idx, src[i + 1].idx, distance, graph_x);
//	}
//
//	std::sort(src.begin(), src.end(), [](Point &a, Point &b) { return a.y < b.y; });
//
//	for (int i = 0; i < n - 1; i++) {
//		int distance = src[i + 1].y - src[i].y;
//		push_edge(src[i].idx, src[i + 1].idx, distance, graph_y);
//	}
//
//	std::vector<std::vector<Node>> graph(n);
//
//	for (int i = 0; i < n; i++) {
//		for (Node node: graph_x[i]) {
//			graph[i].push_back(node);
//		}
//
//		for (Node node: graph_y[i]) {
//			graph[i].push_back(node);
//		}
//	}
//
//	return graph;
//}
//
//int shortest_path(std::vector<std::vector<Node>> graph, int start, int dest, int n) {
//	std::vector<bool> visited(n, false);
//	std::vector<int> dist(n, INT_MAX);
//	std::priority_queue<Node> pq;
//
//	dist[start] = 0;
//	pq.push({start, 0});
//
//	while (!pq.empty()) {
//		int current = pq.top().idx;
//		pq.pop();
//
//		for (Node node: graph[current]) {
//			int i = node.idx;
//			int distance = dist[current] + node.distance;
//
//			if (dist[i] > distance) {
//				dist[i] = distance;
//
//				if (!visited[i]) {
//					pq.push({i, dist[i]});
//				}
//			}
//		}
//
//		visited[current] = true;
//	}
//
//	return dist[dest];
//}
//
//bool compare_nodes(const Node &a, const Node &b) {
//	return a.distance > b.distance;
//}
//
//int main() {
//	std::ios_base::sync_with_stdio(false);
//	std::cout.tie(nullptr);
//	std::cin.tie(nullptr);
//	// -------------------------
//	std::vector<Point> points;
//	int n;
//	int from, to;
//
//	// Input
//	std::cin >> n;
//
//	for (int i = 0; i < n; i++) {
//		int x, y;
//
//		std::cin >> x >> y;
//		points.push_back(Point(i, x, y));
//	}
//
//	std::cin >> from >> to;
//
//	// Processing
//	std::vector<std::vector<Node>> graph = reduce_graph(points, n);
//
//	std::cout << shortest_path(graph, from, to, n);
//
//	//print_graph(graph);
//
//	return 0;
//}
//
///*
//5
//2 2
//1 1
//4 5
//7 1
//6 7
//0 4
//*/