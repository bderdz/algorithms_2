#include <iostream>

typedef std::vector<std::vector<int>> matrix;

struct Vertex {
	int idx;
	std::vector<int> edges;
	char color;

	Vertex(int idx, char color) : idx(idx), color(color) {};
};

typedef std::vector<Vertex> t_graph;

void print_board(matrix &board, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}

std::vector<int> find_all_captures(int x, int y, int type, char color, matrix &board, int n) {
	switch (type) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}

matrix convert_to_bipartite(matrix &graph, int n) {
	t_graph bipartite_graph;

	bool is_black = true;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int figure_type = graph[i][j];

			if (!figure_type) {
				continue;
			}

			char color = is_black ? 'b' : 'w';
			Vertex figure = Vertex(n * i + j, color);

			is_black = !is_black;
		}
	}
}

int main() {
	int n;

	std::cin >> n;

	matrix board(n, std::vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> board[i][j];
		}
	}

	print_board(board, n);

	return 0;
}