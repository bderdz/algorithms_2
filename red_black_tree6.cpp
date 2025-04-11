#include <iostream>
#include <sstream>
#include <unordered_map>
#include <list>


struct Node {
	std::string name;

	Node(std::string &name) : name(name) {}
};

typedef std::unordered_map<std::string, std::list<Node *>::iterator> node_ptr_map;

void swap_nodes(node_ptr_map &map, std::stringstream &stream) {
	std::string name_a, name_b;
	stream >> name_a >> name_b;
	auto a_it = map[name_a];
	auto b_it = map[name_b];
	std::iter_swap(a_it, b_it);
	std::swap(map[name_a], map[name_b]);
}

void move_node(int offset, std::string &key, node_ptr_map &map, std::list<Node *> &list) {
	auto node_it = map[key];

	long int current_idx = std::distance(list.begin(), node_it);
	int new_idx = current_idx - offset;

	if (new_idx == current_idx) return;
	if (new_idx < 0) new_idx = 0;
	if (new_idx >= list.size()) new_idx = list.size() - 1;

	if (new_idx > current_idx) new_idx++;
	auto target_it = list.begin();
	std::advance(target_it, new_idx);

	list.splice(target_it, list, node_it);
	map[key] = std::prev(target_it);
}

void print_list(std::list<Node *> &list) {
	for (Node *node: list) {
		std::cout << node->name << "\n";
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	node_ptr_map map;
	std::list<Node *> list;
	int n, m;

	// INPUT
	std::cin >> n;

	std::string name;
	for (int i = 0; i < n; i++) {
		std::cin >> name;
		Node *new_node = new Node(name);
		auto node_it = list.insert(list.end(), new_node);
		map[name] = node_it;
	}

	std::cin >> m;
	std::string line;
	std::cin.ignore();
	for (int i = 0; i < m; i++) {
		std::getline(std::cin, line);
		std::stringstream stream(line);

		char op;
		stream >> op;
		stream.ignore();

		if (op == 'a') {
			stream >> name;
			Node *new_node = new Node(name);
			auto node_it = list.insert(list.end(), new_node);
			map[name] = node_it;
		} else if (op == 'r') {
			swap_nodes(map, stream);
		} else {
			int offset = 0;
			stream >> name >> offset;
			move_node(offset, name, map, list);
		}
	}

	print_list(list);
	return 0;
}
