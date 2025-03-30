#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

int T = 10;

struct Pair {
	size_t key;
	std::string value;

	Pair(size_t key, std::string &value) {
		this->key = key;
		this->value = value;
	}
};

struct Node {
	int t;
	std::vector<Pair *> pairs;
	bool is_leaf;
	std::vector<Node *> *children;

	Node(int t, bool is_leaf = true) {
		this->t = t;
		this->is_leaf = is_leaf;
		this->children = is_leaf ? nullptr : new std::vector<Node *>();
	}

	void split(Node *parent) {
		Node *split_node = new Node(this->t, false);
		int n = pairs.size();
		int middle = n / 2;

		for (int i = middle + 1; i < n; i++) {
			split_node->pairs.push_back(pairs[i]);
		}
		pairs.erase(pairs.begin() + middle + 1);

		if (!is_leaf) {
			for (int i = middle + 1; i <= n; i++) {
				split_node->children->push_back((*children)[i]);
			}
		}

		parent->pairs.push_back(pairs[middle]);
	};
};

class BTree {
private:
	int t;
	Node *root;

	size_t key_hash(const std::string &key) {
		size_t hash_key = 0;

		for (char c: key) {
			hash_key = hash_key * 31 + c;
		}

		return hash_key;
	}

public:
	BTree(int t) {
		this->root = nullptr;
		this->t = 2 * t - 1;
	};

	void insert(std::string &key, std::string &value) {
		size_t hash_key = key_hash(key);
		Pair *pair = new Pair(hash_key, value);

		if (!root) {
			root = new Node(t);
			root->pairs.push_back(pair);
		} else {
			// Jeżeli root przekroczył liczbę kluczy
			if (root->pairs.size() == t) {

			} else {

			}
		}
	}
};

int main() {
	int n;
	std::unordered_map<std::string, std::string> map;
	std::cin >> n;
	std::cin.ignore();

	BTree tree = BTree(T);

	std::string line;
	for (int i = 0; i < n; i++) {
		std::getline(std::cin, line);

		if (line.find(": ") != std::string::npos) {
			std::string key, value;
			std::stringstream stream(line);
			std::getline(stream, key, ':');
			stream.ignore();
			std::getline(stream, value);

			//			map[key] = value;

		} else {
			//			std::cout << map[line] << "\n";
		}
	}
	list.print_list();

	return 0;
}