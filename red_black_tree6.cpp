#include <iostream>
#include <sstream>
#include <list>

struct ListNode {
	std::string name;

	ListNode(std::string &name) : name(name) {}
};


struct TreeNode {
	size_t key;
	std::list<ListNode *>::iterator value;
	char color;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;

	TreeNode(size_t key) {
		this->key = key;
		this->color = 'R';
		this->left = this->right = this->parent = nullptr;
	}
};

class RedBlackTree {
private:
	TreeNode *root;
	TreeNode *NIL;

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

	void fix_insert(TreeNode *curr) {
		while (curr != root && curr->parent->color == 'R') {
			if (curr->parent == curr->parent->parent->left) {
				TreeNode *uncle = curr->parent->parent->right;
				if (uncle->color == 'R') {
					curr->parent->color = 'B';
					uncle->color = 'B';
					curr->parent->parent->color = 'R';
					curr = curr->parent->parent;
				} else {
					if (curr == curr->parent->right) {
						curr = curr->parent;
						left_rotate(curr);
					}
					curr->parent->color = 'B';
					curr->parent->parent->color = 'R';
					right_rotate(curr->parent->parent);
				}
			} else {
				TreeNode *uncle = curr->parent->parent->left;
				if (uncle->color == 'R') {
					curr->parent->color = 'B';
					uncle->color = 'B';
					curr->parent->parent->color = 'R';
					curr = curr->parent->parent;
				} else {
					if (curr == curr->parent->left) {
						curr = curr->parent;
						right_rotate(curr);
					}
					curr->parent->color = 'B';
					curr->parent->parent->color = 'R';
					left_rotate(curr->parent->parent);
				}
			}
		}
		root->color = 'B';
	}

	TreeNode *tree_search(TreeNode *node, size_t key) {
		if (node == NIL || key == node->key) {
			return node;
		}

		if (key < node->key) {
			return tree_search(node->left, key);
		}

		return tree_search(node->right, key);
	}

	void cut_tree(TreeNode *node) {
		if (node == NIL) return;
		cut_tree(node->left);
		cut_tree(node->right);
		delete node;
	}

public:
	RedBlackTree() {
		this->NIL = new TreeNode(-1);
		NIL->color = 'B';
		NIL->left = NIL->right = NIL;
		this->root = NIL;
	}

	void insert(size_t key, std::list<ListNode *>::iterator &value) {
		TreeNode *new_node = new TreeNode(key);
		new_node->value = value;
		new_node->left = new_node->right = new_node->parent = NIL;

		TreeNode *parent = nullptr;
		TreeNode *current = root;
		while (current != NIL) {
			parent = current;
			if (new_node->key < parent->key) current = current->left;
			else current = current->right;
		}

		new_node->parent = parent;
		if (parent == nullptr) root = new_node;
		else if (new_node->key < parent->key) parent->left = new_node;
		else parent->right = new_node;

		if (new_node->parent == nullptr) {
			new_node->color = 'B';
			return;
		}

		if (new_node->parent->parent == nullptr) return;

		fix_insert(new_node);
	}

	TreeNode *search(size_t key) {
		return tree_search(root, key);
	}

	~RedBlackTree() {
		cut_tree(root);
		delete NIL;
	}
};


class DangerousBoard {
private:
	RedBlackTree map;
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
	DangerousBoard() {
		this->map = RedBlackTree();
	}

	void swap_nodes(std::string &name_a, std::string &name_b) {
		size_t key_a, key_b;
		key_a = key_hash(name_a);
		key_b = key_hash(name_b);

		TreeNode *a = map.search(key_a);
		TreeNode *b = map.search(key_b);

		std::iter_swap(a->value, b->value);
		std::swap(a->value, b->value);
	}

	void move_node(int offset, std::string &key) {
		size_t hash_key = key_hash(key);
		auto node = map.search(hash_key);
		auto target_it = node->value;

		for (int i = 0; i < std::abs(offset); i++) {
			if (offset > 0) target_it--;
			else target_it++;

			if (target_it == list.begin() && target_it == list.end()) break;
		}

		if (offset < 0) target_it++;
		list.splice(target_it, list, node->value);
		node->value = std::prev(target_it);
	}

	void add_node(std::string &name) {
		ListNode *new_node = new ListNode(name);
		auto node_it = list.insert(list.end(), new_node);
		map.insert(key_hash(name), node_it);
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