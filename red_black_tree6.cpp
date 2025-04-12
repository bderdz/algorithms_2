#include <iostream>
#include <sstream>
#include <unordered_map>
#include <list>

struct ListNode {
	std::string name;

	ListNode(std::string &name) : name(name) {}
};

typedef std::unordered_map<size_t, std::list<ListNode *>::iterator> node_ptr_map;

class RedBlackTree {
private:
	struct TreeNode {
		size_t key;
		std::list<ListNode *>::iterator value;
		char color;
		TreeNode *parent;
		TreeNode *left;
		TreeNode *right;

		TreeNode(size_t key, TreeNode *parent = nullptr) {
			this->key = key;
			this->parent = parent;
			this->left = this->right = nullptr;
		}
	};

	void left_rotate(TreeNode *x) {
		TreeNode *y = x->right;
		x->right = y->left;
		if (y->left != NIL) y->left->parent = x;

		y->parent = x->parent;
		if (x->parent == nullptr) root = y;
		else if (x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;

		y->left = x;
		x->parent = y;
	}

	void right_rotate(TreeNode *x) {
		TreeNode *y = x->left;
		x->left = y->right;
		if (y->right != NIL) y->right->parent = x;

		y->parent = x->parent;
		if (x->parent == nullptr) root = y;
		else if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;

		y->right = x;
		x->parent = y;
	}

	TreeNode *root;
	TreeNode *NIL;
public:
	RedBlackTree() {
		this->NIL = new TreeNode(-1);
		NIL->color = 'B';
		NIL->left = NIL->right = NIL;
		this->root = NIL;
	}
};


class DangerousBoard {
private:
	node_ptr_map map;
	std::list<ListNode *> list;

	size_t key_hash(const std::string &str) {
		size_t hash = 2166136261u;
		for (char c: str) {
			hash ^= static_cast<size_t>(c);
			hash *= 16777619u;
		}
		return hash;
	}

public:
	DangerousBoard() {}

	void swap_nodes(std::string &name_a, std::string &name_b) {
		size_t key_a, key_b;
		key_a = key_hash(name_a);
		key_b = key_hash(name_b);

		auto a_it = map[key_a];
		auto b_it = map[key_b];
		std::iter_swap(a_it, b_it);
		std::swap(map[key_a], map[key_b]);
	}

	void move_node(int offset, std::string &key) {
		size_t hash_key = key_hash(key);
		auto node_it = map[hash_key];
		auto target_it = node_it;

		for (int i = 0; i < std::abs(offset); i++) {
			if (offset > 0) target_it--;
			else target_it++;

			if (target_it == list.begin() && target_it == list.end()) break;
		}

		if (offset < 0) target_it++;
		list.splice(target_it, list, node_it);
		map[hash_key] = std::prev(target_it);
	}

	void add_node(std::string &name) {
		ListNode *new_node = new ListNode(name);
		auto node_it = list.insert(list.end(), new_node);
		map[key_hash(name)] = node_it;
	}

	void print_board() {
		for (ListNode *node: list) {
			std::cout << node->name << "\n";
		}
	}

	~DangerousBoard() {
		for (ListNode *node: list) delete node;
	}
};


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	DangerousBoard board;
	unsigned int n, m;
	// INPUT
	std::cin >> n;

	std::string name;
	for (unsigned int i = 0; i < n; i++) {
		std::cin >> name;
		board.add_node(name);
	}

	std::cin >> m;
	std::string line;
	std::cin.ignore();
	for (unsigned int i = 0; i < m; i++) {
		std::getline(std::cin, line);
		std::stringstream stream(line);

		char op;
		stream >> op;
		stream.ignore();
		if (op == 'a') {
			stream >> name;
			board.add_node(name);
		} else if (op == 'r') {
			std::string name_a, name_b;
			stream >> name_a >> name_b;
			board.swap_nodes(name_a, name_b);
		} else {
			int offset = 0;
			stream >> name >> offset;
			board.move_node(offset, name);
		}
	}

	board.print_board();
	return 0;
}