#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>

struct Node {
	int v;
	Node *left;
	Node *right;

	Node(int v) {
		this->left = this->right = nullptr;
		this->v = v;
	}
};

class BST {
private:
	Node *root;

	Node *trim_bst(Node *root, int a, int b) {
		if (!root) return nullptr;

		if (root->v < a) {
			Node *right_sub = trim_bst(root->right, a, b);
			delete root;
			return right_sub;
		}

		if (root->v > b) {
			Node *left_sub = trim_bst(root->left, a, b);
			delete root;
			return left_sub;
		}

		root->left = trim_bst(root->left, a, b);
		root->right = trim_bst(root->right, a, b);

		return root;
	}

public:
	BST() {
		this->root = nullptr;
	}

	Node *get_root() {
		return root;
	}

	void add(int v) {
		if (root == nullptr) {
			root = new Node(v);
			return;
		}

		Node *current = root;
		while (current != nullptr) {
			if (v < current->v) {
				if (current->left == nullptr) {
					current->left = new Node(v);
					break;
				}

				current = current->left;
			} else {
				if (current->right == nullptr) {
					current->right = new Node(v);
					break;
				}

				current = current->right;
			}
		}
	}


	void trim(int a, int b) {
		root = trim_bst(root, a, b);
	}

	void inorder_vector(Node *root, std::vector<int> &output) {
		if (root == nullptr) return;

		inorder_vector(root->left, output);
		output.push_back(root->v);
		inorder_vector(root->right, output);
	}

	void delete_tree(Node *node) {
		if (node != nullptr) {
			delete_tree(node->right);
			delete_tree(node->left);
			delete node;
		}
	}

	~BST() {
		delete_tree(root);
	}
};

void find_closest_path(std::vector<int> &paths, int sum) {
	std::unordered_set<int> closest;

	for (int v: paths) {
		auto iter = closest.find(sum - v);
		if (iter != closest.end()) {
			std::cout << std::min(v, *iter) << " " << std::max(v, *iter) << "\n";
			return;
		}

		closest.insert(v);
	}

	std::cout << "NIE ZNALEZIONO";
}

int main() {
	int n;
	int a, b;
	int k;
	BST *political_paths = new BST();

	std::cin >> n;

	for (int i = 0; i < n; i++) {
		int v;
		std::cin >> v;

		political_paths->add(v);
	}

	std::cin >> a >> b >> k;

	political_paths->trim(a, b);
	std::vector<int> inorder_paths;
	political_paths->inorder_vector(political_paths->get_root(), inorder_paths);
	find_closest_path(inorder_paths, k);

	delete political_paths;
	return 0;
}