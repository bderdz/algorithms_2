#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

struct Node {

};

class BTree {
private:
public:
};

int main() {
	int n;
	std::unordered_map<std::string, std::string> map;
	std::cin >> n;
	std::cin.ignore();

	std::string line;
	for (int i = 0; i < n; i++) {
		std::getline(std::cin, line);

		if (line.find(": ") != std::string::npos) {
			std::string key, value;
			std::stringstream stream(line);
			std::getline(stream, key, ':');
			stream.ignore();
			std::getline(stream, value);

			map[key] = value;
		} else {
			std::cout << map[line] << "\n";
		}

	}
	return 0;
}