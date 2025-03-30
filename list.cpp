
struct Pair {
	size_t key;
	std::string value;
	Pair *prev;
	Pair *next;

	Pair(size_t key, std::string &value) {
		this->key = key;
		this->value = value;
		this->prev = this->next = nullptr;
	}
};

class List {
private:
	int n;
public:
	Pair *head;
	Pair *tail;

	List() {
		this->head = nullptr;
		this->tail = head;
		this->n = 0;
	}

	void push(size_t key, std::string &value) {
		Pair *new_element = new Pair(key, value);
		n++;

		if (!head) {
			head = tail = new_element;
			return;
		} else if (head->key > key) {
			new_element->next = head;
			head->prev = new_element;
			head = new_element;
			return;
		}

		Pair *current = head;
		while (current->next && current->next->key < key) {
			current = current->next;
		}

		new_element->next = current->next;
		new_element->prev = current;
		current->next = new_element;
		if (new_element->next) {
			new_element->next->prev = new_element;
		} else {
			tail = new_element;
		}
	};

	//	int pop() {
	//	};

	int size() const {
		return this->n;
	}

	bool empty() const {
		return head == nullptr;
	}

	~List() {
		while (head != nullptr) {
			Pair *tmp = head;
			head = tmp->next;
			delete tmp;
		}

		tail = nullptr;
	}

	void print_list() {
		Pair *current = head;

		while (current) {
			std::cout << current->key << " " << current->value << "\n";
			current = current->next;
		}
	}
};

