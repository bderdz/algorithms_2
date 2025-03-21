#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits.h>

struct Point {
	int i;
	int d;

	Point(int i, int d) : i(i), d(d) {};
};

struct Vertex {
	int idx;
	int type;
	std::vector<int> edges;
	bool is_black;
	int edge;

	Vertex(int idx, int type, bool is_black) {
		this->idx = idx;
		this->type = type;
		this->is_black = is_black;
		this->edge = -1;
	};
};

typedef std::vector<std::vector<int>> matrix;
typedef std::vector<Vertex> t_graph;

//* DEBUG
void print_graph(matrix &graph, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << "\n";
	}
}


class BipChess {
public:
	t_graph bip_graph;
	std::vector<int> dist;
	std::unordered_map<int, int> index_map;
	int n;
	int max_captures;

public:
	BipChess(matrix &graph, int n) {
		this->n = 0;
		this->max_captures = 0;

		convert_to_bipartite(graph, n);
	}

	int bfs(std::queue<int> &free) {
		int height = INT_MAX;
		std::queue<Point> queue;

		for (int i = 0; i < n; i++) {
			if (bip_graph[i].is_black && bip_graph[i].edge == -1) {
				dist[i] = 0;
				queue.push({i, 0});
				free.push(i);
			} else {
				dist[i] = INT_MAX;
			}
		}

		while (!queue.empty()) {
			Point current = queue.front();
			queue.pop();

			if (current.d < height) {    //! Przerwać jeśli przekroczyło ?
				for (int e: bip_graph[current.i].edges) {
					int nbr_idx = index_map[e];
					Vertex &nbr = bip_graph[nbr_idx];

					if (dist[nbr_idx] >= current.d + 1) {
						dist[nbr_idx] = current.d + 1;
						queue.push({nbr_idx, current.d + 1});

						if (nbr.edge == -1 && !nbr.is_black) {
							height = std::min(height, current.d + 1);
						}
					}
				}
			} else {
				break;
			}


		}

		return height;
	}

	bool dfs(int i, int h, int max_h, bool is_black = true) {
		if (h < max_h) {
			for (int e: bip_graph[i].edges) {
				e = index_map[e];
				if (dist[e] == dist[i] + 1) {
					if (dfs(e, h + 1, max_h, !is_black)) {
						if (is_black) {
							bip_graph[i].edge = e;
							bip_graph[e].edge = i;
						} else {
							bip_graph[i].edge = -1;
						}

						return true;
					}

					return false;
				}
			}
		} else if (h == max_h) {
			if (bip_graph[i].edge == -1 && !bip_graph[i].is_black) {
				dist[i] = h;
				return true;
			}
		}
		return false;
	}

	int max_association() {
		dist = std::vector<int>(n, INT_MAX);
		std::queue<int> free;
		int height = 0;
		max_captures = 0;

		int current_height = bfs(free);

		while (current_height > height) {
			height = current_height;
			std::cout << "HEIGHT: " << height << " MAX " << max_captures << "\n";
			for (int i = 0; i < n; i++) {
				std::cout << dist[i] << " ";
			}

			std::cout << "\n";

			while (!free.empty()) {
				int free_v = free.front();
				free.pop();

				if (dfs(free_v, 0, height)) {
					max_captures++;
				}
			}

			current_height = bfs(free);
		}
		//		while (!free.empty()) {
		//			std::cout << free.front() << " ";
		//			free.pop();
		//		}
		//		std::cout << "\n";


		std::cout << max_captures << "\n";


		return max_captures;
	}

	void add_captured(int white_idx, int white_type, Vertex &black_v) {
		black_v.edges.push_back(white_idx);
		//* Jeżeli nie mamy zmapowanego indeksu tworzymy wierzchołek i dodajemy krawędź
		if (index_map.find(white_idx) == index_map.end()) {
			Vertex captured_v = Vertex(white_idx, white_type, false);
			captured_v.edges.push_back(black_v.idx);

			index_map.insert({white_idx, bip_graph.size()});
			bip_graph.push_back(captured_v);
		} else {
			bip_graph[index_map[white_idx]].edges.push_back(black_v.idx);
		}
	}

	//* Tworzenie listy sąsiedztwa dla wierzchołków
	//! DO POPRAWY
	void find_all_captures(Vertex &v, int x, int y, matrix &board, int size) {
		switch (v.type) {
			case 1:
				//* 3 do przodu
				if (x + 3 < size && board[y][x + 3]) {
					int captured_idx = size * y + x + 3;
					add_captured(captured_idx, board[y][x + 3], v);
				}
				//* 2 do przodu + 1 lewo/prawo
				if (x + 2 < size) {
					int captured_idx = v.idx - size + 2;
					if (y - 1 >= 0 && board[y - 1][x + 2]) {
						add_captured(captured_idx, board[y - 1][x + 2], v);
					}

					captured_idx = v.idx + size + 2;
					if (y + 1 < size && board[y + 1][x + 2]) {
						add_captured(captured_idx, board[y + 1][x + 2], v);
					}
				}
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				break;
		}
	}

	//* Tworzenie grafu dwudzielnego
	void convert_to_bipartite(matrix &graph, int size) {
		bip_graph = std::vector<Vertex>();
		index_map = std::unordered_map<int, int>();

		for (int i = 0; i < size; i++) {
			for (int j = i % 2; j < size; j += 2) {
				int figure_type = graph[i][j];
				if (figure_type) {
					Vertex figure = Vertex(size * i + j, figure_type, true);

					find_all_captures(figure, j, i, graph, size);
					if (figure.edges.empty()) continue;

					index_map.insert({figure.idx, bip_graph.size()});
					bip_graph.push_back(figure);
				}
			}
		}

		this->n = bip_graph.size();
	}

	//* DEBUG
	void print_graph() {
		for (Vertex &v: bip_graph) {
			std::cout << v.idx << " " << (v.is_black ? 'b' : 'w') << " [";

			for (int e: v.edges) {
				std::cout << e << ", ";
			}
			std::cout << "]\n";
		}
		std::cout << "\n";
	}
};


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	matrix board(n, std::vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> board[i][j];
		}
	}


	BipChess bip_board = BipChess(board, n);
	bip_board.print_graph();
	std::cout << bip_board.n << "\n";
	bip_board.max_association();

	return 0;
}