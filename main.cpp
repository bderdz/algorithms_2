//#include <iostream>
//
//class BST {
//private:
//	struct Node {
//		int v;
//		Node *left;
//		Node *right;
//
//		Node(int v) {
//			this->left = this->right = nullptr;
//			this->v = v;
//		}
//	};
//
//	Node *root;
//public:
//	BST() {
//		this->root = nullptr;
//	}
//
//	void add(int v) {
//		if (root == nullptr) {
//			root = new Node(v);
//			return;
//		}
//
//		Node *current = root;
//
//		while (current != nullptr) {
//			if (f < current->f || (f == current->f && l < current->l)) {
//				if (current->left == nullptr) {
//					current->left = new Node(f, l);
//					break;
//				}
//
//				current = current->left;
//			} else {
//				if (current->right == nullptr) {
//					current->right = new Node(f, l);
//					break;
//				}
//
//				current = current->right;
//			}
//		}
//	}
//};
//
//int main() {
//	int n;
//	int a, b;
//	int k;
//
//	std::cin >> n;
//
//	for (int i = 0; i < n; i++) {
//		int v;
//		std::cin >> v;
//	}
//
//	std::cin >> a >> b >> k;
//
//	return 0;
//}