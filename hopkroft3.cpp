//#include <iostream>
//#include <vector>
//#include <queue>
//#include <unordered_map>
//#include <limits.h>
//
//struct Point {
//	int i;
//	int d;
//
//	Point(int i, int d) : i(i), d(d) {};
//};
//
//struct Vertex {
//	std::vector<int> edges;
//	int idx;
//	int type;
//	bool is_black;
//	int edge;
//
//	Vertex(int idx, int type, bool is_black) {
//		this->idx = idx;
//		this->type = type;
//		this->is_black = is_black;
//		this->edge = -1;
//	};
//};
//
//typedef std::vector<std::vector<int>> matrix;
//typedef std::vector<Vertex> t_graph;
//
//class BipChess {
//private:
//	t_graph bip_graph;
//	std::vector<int> dist;
//	std::unordered_map<int, int> index_map;
//	int n;
//	int max_captures;
//
//public:
//	BipChess(matrix &graph, int n) {
//		this->max_captures = 0;
//		this->n = convert_to_bipartite(graph, n);
//	}
//
//	void add_captured(int captured_idx, int captured_type, Vertex &black_v) {
//		black_v.edges.push_back(captured_idx);
//		//* Jeżeli nie mamy zmapowanego indeksu, tworzymy wierzchołek i dodajemy krawędź
//		if (index_map.find(captured_idx) == index_map.end()) {
//			Vertex captured_v = Vertex(captured_idx, captured_type, false);
//			captured_v.edges.push_back(black_v.idx);
//
//			index_map.insert({captured_idx, bip_graph.size()});
//			bip_graph.push_back(captured_v);
//		} else {
//			bip_graph[index_map[captured_idx]].edges.push_back(black_v.idx);
//		}
//	}
//
//	//* Tworzenie listy sąsiedztwa dla wierzchołków
//	void find_all_captures(Vertex &v, int x, int y, matrix &board, int size) {
//		int tx, ty, captured_idx, captured_type;
//		switch (v.type) {
//			case 1:
//				//* 3 do przodu
//				tx = x + 3;
//				ty = y;
//				if (tx < size && board[ty][tx]) {
//					captured_idx = size * ty + tx;
//					captured_type = board[ty][tx];
//					add_captured(captured_idx, captured_type, v);
//				}
//				//* 2 do przodu 1 lewo/prawo
//				tx = x + 2;
//				if (tx < size) {
//					ty = y - 1;
//					if (ty >= 0 && board[ty][tx]) {
//						captured_idx = size * ty + tx;
//						captured_type = board[ty][tx];
//						add_captured(captured_idx, captured_type, v);
//					}
//
//					ty = y + 1;
//					if (ty < size && board[ty][tx]) {
//						captured_idx = size * ty + tx;
//						captured_type = board[ty][tx];
//						add_captured(captured_idx, captured_type, v);
//					}
//				}
//				break;
//			case 2:
//				//* 1 do przodu
//				tx = x + 1;
//				ty = y;
//				if (tx < size && board[ty][tx]) {
//					captured_idx = size * ty + tx;
//					captured_type = board[ty][tx];
//					add_captured(captured_idx, captured_type, v);
//				}
//
//				//* 1 prawo
//				tx = x;
//				ty = y + 1;
//				if (ty < size && board[ty][tx]) {
//					captured_idx = size * ty + tx;
//					captured_type = board[ty][tx];
//					add_captured(captured_idx, captured_type, v);
//				}
//				//* 1 lewo
//				ty = y - 1;
//				if (ty >= 0 && board[ty][tx]) {
//					captured_idx = size * ty + tx;
//					captured_type = board[ty][tx];
//					add_captured(captured_idx, captured_type, v);
//				}
//				break;
//			case 3:
//				//* 1 do przodu
//				tx = x + 1;
//				ty = y;
//				if (tx < size && board[ty][tx]) {
//					captured_idx = size * ty + tx;
//					captured_type = board[ty][tx];
//					add_captured(captured_idx, captured_type, v);
//				}
//				//* 2 do przodu 1 lewo/prawo
//				tx = x + 2;
//				if (tx < size) {
//					ty = y - 1;
//					if (ty >= 0 && board[ty][tx]) {
//						captured_idx = size * ty + tx;
//						captured_type = board[ty][tx];
//						add_captured(captured_idx, captured_type, v);
//					}
//
//					ty = y + 1;
//					if (ty < size && board[ty][tx]) {
//						captured_idx = size * ty + tx;
//						captured_type = board[ty][tx];
//						add_captured(captured_idx, captured_type, v);
//					}
//				}
//				break;
//			default:
//				break;
//		}
//	}
//
//	//* Tworzenie grafu dwudzielnego
//	int convert_to_bipartite(matrix &graph, int size) {
//		bip_graph = std::vector<Vertex>();
//		index_map = std::unordered_map<int, int>();
//
//		for (int i = 0; i < size; i++) {
//			for (int j = i % 2; j < size; j += 2) {
//				int pawn_type = graph[i][j];
//				if (pawn_type) {
//					Vertex pawn = Vertex(size * i + j, pawn_type, true);
//
//					find_all_captures(pawn, j, i, graph, size);
//					if (pawn.edges.empty()) continue;
//
//					index_map.insert({pawn.idx, bip_graph.size()});
//					bip_graph.push_back(pawn);
//				}
//			}
//		}
//		return bip_graph.size();
//	}
//
//	int bfs(std::queue<int> &free) {
//		int height = INT_MAX;
//		std::queue<Point> queue;
//
//		for (int i = 0; i < n; i++) {
//			if (bip_graph[i].is_black && bip_graph[i].edge == -1) {
//				dist[i] = 0;
//				queue.push({i, 0});
//				free.push(i);
//			} else {
//				dist[i] = INT_MAX;
//			}
//		}
//
//		while (!queue.empty()) {
//			Point current = queue.front();
//			queue.pop();
//
//			if (current.d <= height) {
//				if (!bip_graph[current.i].is_black && bip_graph[current.i].edge != -1) {
//					int nbr_idx = index_map[bip_graph[current.i].edge];
//					dist[nbr_idx] = current.d + 1;
//					queue.push({nbr_idx, current.d + 1});
//					continue;
//				}
//
//				for (int e: bip_graph[current.i].edges) {
//					int nbr_idx = index_map[e];
//					Vertex &nbr = bip_graph[nbr_idx];
//
//					if (dist[nbr_idx] >= current.d + 1) {
//						dist[nbr_idx] = current.d + 1;
//
//						if (nbr.edge == -1 && !nbr.is_black) {
//							height = std::min(height, current.d + 1);
//							continue;
//						}
//
//						queue.push({nbr_idx, current.d + 1});
//					}
//				}
//			} else {
//				break;
//			}
//		}
//
//		return height;
//	}
//
//	bool dfs(int i, int h, int max_h) {
//		if (h < max_h) {
//			if (!bip_graph[i].is_black) {
//				return dfs(index_map[bip_graph[i].edge], h + 1, max_h);
//			}
//
//			for (int e: bip_graph[i].edges) {
//				int e_idx = index_map[e];
//
//				if (dist[e_idx] == dist[i] + 1 && dfs(e_idx, h + 1, max_h)) {
//					if (bip_graph[i].is_black) {
//						bip_graph[i].edge = e;
//						bip_graph[e_idx].edge = bip_graph[i].idx;
//					}
//					return true;
//				}
//			}
//		} else if (!bip_graph[i].is_black && bip_graph[i].edge == -1) {
//			return true;
//		}
//		return false;
//	}
//
//	int max_association() {
//		dist = std::vector<int>(n, INT_MAX);
//		std::queue<int> free;
//		int height = 0;
//		int current_height;
//		max_captures = 0;
//
//		while ((current_height = bfs(free)) > height) {
//			height = current_height;
//
//			while (!free.empty()) {
//				int free_v = free.front();
//				free.pop();
//
//				if (bip_graph[free_v].edge == -1 && dfs(free_v, 0, height)) {
//					max_captures++;
//				}
//			}
//		}
//		return max_captures;
//	}
//};
//
//int main() {
//	std::ios_base::sync_with_stdio(false);
//	std::cout.tie(nullptr);
//	std::cin.tie(nullptr);
//
//	int n;
//	std::cin >> n;
//	// Wczytywanie szachownicy
//	matrix board(n, std::vector<int>(n));
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			std::cin >> board[i][j];
//		}
//	}
//	// Przetwarzanie
//	BipChess bip_board = BipChess(board, n);
//	int max_captures = bip_board.max_association();
//	// OUTPUT
//	std::cout << n * n - max_captures << "\n";
//	return 0;
//}