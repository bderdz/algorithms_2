//#include <iostream>
//#include <string>
//#include <sstream>
//#include <vector>
//#include <utility>
//
//int T = 15;
//
//struct Pair {
//	size_t key;
//	std::string value;
//
//	Pair(size_t key, std::string &value) {
//		this->key = key;
//		this->value = value;
//	}
//};
//
//struct Node {
//	int t;
//	std::vector<Pair *> pairs;
//	bool is_leaf;
//	Node **children;
//
//	Node(int t, bool is_leaf) {
//		this->t = t;
//		this->is_leaf = is_leaf;
//		this->children = new Node *[t + 1]();
//	}
//
//	std::string search(size_t key) {
//		int i = 0;
//		while (i < pairs.size() && key > pairs[i]->key)
//			i++;
//
//		if (i < pairs.size() && pairs[i]->key == key)
//			return pairs[i]->value;
//
//		if (is_leaf || children[i] == nullptr) return "BRAK";
//
//		return children[i]->search(key);
//	}
//
//	bool insert(Pair *pair) {
//		int i = 0;
//		while (i < pairs.size() && pair->key > pairs[i]->key) {
//			i++;
//		}
//		// Sprawdzenie, czy klucz już istnieje
//		if (i < pairs.size() && pairs[i]->key == pair->key) {
//			pairs[i]->value = pair->value;
//			delete pair;
//		} else if (is_leaf) {
//			pairs.insert(pairs.begin() + i, pair);
//		} else {
//			bool is_full = children[i]->insert(pair);
//
//			if (is_full) {
//				std::pair<Pair *, Node *> result = split(children[i]);
//				Pair *middle = result.first;
//				Node *right_node = result.second;
//
//				while (i < pairs.size() && middle->key > pairs[i]->key) {
//					i++;
//				}
//
//				pairs.insert(pairs.begin() + i, middle);
//				for (size_t j = pairs.size(); j > i + 1; j--) {
//					children[j] = children[j - 1];
//				}
//
//				children[i + 1] = right_node;
//			}
//		}
//
//		return pairs.size() == t;
//	}
//
//	std::pair<Pair *, Node *> split(Node *node) {
//		Node *right_node = new Node(this->t, node->is_leaf);
//		int middle_i = node->pairs.size() / 2;
//		Pair *middle = node->pairs[middle_i];
//		// Kopiujemy pary key-value większe od middle do right_node
//		right_node->pairs.assign(node->pairs.begin() + middle_i + 1, node->pairs.end());
//		// Kopiujemy dzieci większe od middle do right_node
//		if (!node->is_leaf) {
//			for (size_t i = 0; i <= right_node->pairs.size(); i++) {
//				if (node->children[middle_i + i + 1]) {
//					right_node->children[i] = node->children[middle_i + i + 1];
//					node->children[middle_i + i + 1] = nullptr;
//				}
//			}
//		}
//		node->pairs.resize(middle_i);
//		return std::make_pair(middle, right_node);
//	};
//
//	~Node() {
//		if (!is_leaf) {
//			for (size_t i = 0; i <= pairs.size(); i++) {
//				if (children[i]) delete children[i];
//			}
//			delete[] children;
//		}
//
//		for (Pair *p: pairs) {
//			delete p;
//		}
//	}
//};
//
//class BTree {
//private:
//	int t;
//	Node *root;
//
//	size_t key_hash(const std::string &str) {
//		size_t hash = 2166136261u;
//		for (char c: str) {
//			hash ^= static_cast<size_t>(c);
//			hash *= 16777619u;
//		}
//		return hash;
//	}
//
//public:
//	BTree(int t) {
//		this->root = nullptr;
//		this->t = 2 * t - 1;
//	};
//
//	std::string search(std::string &key) {
//		if (!root) return "BRAK";
//		size_t hash_key = key_hash(key);
//		return root->search(hash_key);
//	}
//
//	void insert(std::string &key, std::string &value) {
//		size_t hash_key = key_hash(key);
//		Pair *pair = new Pair(hash_key, value);
//		// Jeżeli drzewo jest puste
//		if (!root) {
//			root = new Node(t, true);
//			root->pairs.push_back(pair);
//		} else {
//			bool is_full = root->insert(pair);
//			if (is_full) {
//				std::pair<Pair *, Node *> result = root->split(root);
//				Pair *middle = result.first;
//				Node *right_node = result.second;
//				Node *new_root = new Node(t, false);
//
//				new_root->pairs.push_back(middle);
//				new_root->children[0] = root;
//				new_root->children[1] = right_node;
//				root = new_root;
//			}
//		}
//	}
//
//	~BTree() {
//		delete root;
//	}
//};
//
//int main() {
//	std::ios_base::sync_with_stdio(false);
//	std::cout.tie(nullptr);
//	std::cin.tie(nullptr);
//
//	BTree tree = BTree(T);
//	int n;
//	std::cin >> n;
//	std::cin.ignore();
//
//	std::string line;
//	for (int i = 0; i < n; i++) {
//		std::getline(std::cin, line);
//
//		if (line.find(": ") != std::string::npos) {
//			std::string key, value;
//			std::stringstream stream(line);
//			std::getline(stream, key, ':');
//			stream.ignore();
//			std::getline(stream, value);
//
//			tree.insert(key, value);
//		} else {
//			std::cout << tree.search(line) << "\n";
//		}
//	}
//
//	return 0;
//}