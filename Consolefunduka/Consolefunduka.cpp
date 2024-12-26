#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct GovNumber {
	char letter;
	int data;
	string word;

	bool operator<(const GovNumber& buf) {
		if (letter != buf.letter) {
			return letter < buf.letter;
		}
		if (data != buf.data) {
			return data < buf.data;
		}
		if (word != buf.word) {
			return word < buf.word;
		}
	}

	bool operator==(const GovNumber& other) const {
		return letter == other.letter &&
			data == other.data &&
			word == other.word;
	}

	bool operator>=(const GovNumber& buf) const {
		return letter >= buf.letter &&
			data >= buf.data &&
			word >= buf.word;
	}

	bool operator<=(const GovNumber& other) const {
		return letter <= other.letter &&
			data <= other.data &&
			word <= other.word;
	}

	bool operator>(const GovNumber& other) const {
		return letter > other.letter &&
			data > other.data &&
			word > other.word;
	}
};
struct TreeNode {
	GovNumber gn;
	TreeNode* left;
	TreeNode* right;
	int bal;
	TreeNode(GovNumber data) {
		bal = 0;
		left = nullptr;
		right = nullptr;
		gn = data;
	}
};

struct Node {
	GovNumber val;
	Node* next;

	Node(GovNumber value) {
		val = value;
		next = nullptr;
	}
};
class List {
public:
	Node* head;
	Node* tail;
	int size;

	List() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	void append(GovNumber data) {
		Node* newNode = new Node(data);
		size++;
		if (head == nullptr) { //список пустой
			head = newNode;
			tail = newNode;
			head->next = tail;
			//tail->next = head;
		}
		else if (head == tail) { //список из одного элемента
			// когда добавляемый элемент оказался меньше единственного элемента в списке
			// это значит что он должен оказаться на последнем месте 
			if (head->val >= data) {
				// tail->val = data
				tail = newNode;
				head->next = tail;
				tail->next = head;
			}
			// если добавляемый элемент оказался больше чем единственный элемент в списке
			// это значит что он должен оказаться на первом месте 
			else if (head->val < data) {
				/*int temp = head->val;
				head->val = data;
				tail->val = temp;*/

				Node* copy = head; // создаем копию для предыдущий головы 
				head = newNode;
				tail = copy;
				head->next = tail;
				tail->next = head;
				//выше норм вроде бы
			}
		}
		else { //список 2 и более элементов
			Node* current = head;
			Node* oldhead = head;
			Node* oldtail = tail;
			if (head->val <= data) {
				/*newNode->next = oldhead;
				head = newNode;
				tail->next = head;*/
				//Node* newNode = new Node(data);
				newNode->next = head;
				tail->next = newNode;
				head = newNode;
				//выше правильно вроде бы
			}
			else if (tail->val > data) {
				/*oldtail->next = newNode;
				tail = newNode;
				tail->next = head;*/
				Node* newNode = new Node(data);
				tail->next = newNode;
				newNode->next = head;
				tail = newNode;
			}
			else {
				while (data < current->val) {
					if (data >= current->next->val) {
						Node* next = current->next;
						//Node* newNode = new Node(data);
						current->next = newNode;
						newNode->next = next;
						current = current->next;
						//Node* temp = current->next;
						//current->next = newNode;
						//newNode->next = temp;
					}
					else {
						current = current->next;
					}
				}
			}
		}
	}

	void print1() {
		Node* temp = head;
		if ((size == 0) || (head == nullptr)) {
			std::cout << "spisok pust\n";
			return;
		}
		else {
			do {
				std::cout << temp->val.letter << temp->val.data << temp->val.word << " ";
				temp = temp->next;
			} while (temp != head);
			std::cout << "\n";
		}
	}
};

void tree_insert(TreeNode*& node, GovNumber data, bool& h, List& list) {
	if (node == nullptr) {
		node = new TreeNode(data);
		h = true;
		return;
	}
	if (data == node->gn) {
		list.append(data);
		return;
	}
	if (data < node->gn) {
		tree_insert(node->left, data, h, list);
		if (h) {
			if (node->bal == 1) {
				node->bal = 0;
				h = false;
			}
			else if (node->bal == 0) {
				node->bal = -1;
			}
			else { // p->bal == -1
				// Балансировка
				TreeNode* p1 = node->left;
				if (p1->bal == -1) {
					// Малый правый поворот
					node->left = p1->right;
					p1->right = node;
					node->bal = 0;
					node = p1;
				}
				else {
					// Большой правый поворот
					TreeNode* p2 = p1->right;
					p1->right = p2->left;
					p2->left = p1;
					node->left = p2->right;
					p2->right = node;
					node->bal = (p2->bal == -1) ? 1 : 0;
					p1->bal = (p2->bal == 1) ? -1 : 0;
					node = p2;
				}
				node->bal = 0;
				h = false;
			}
		}
	}
	else {
		tree_insert(node->right, data, h, list);
		if (h) {
			if (node->bal == -1) {
				node->bal = 0;
				h = false;
			}
			else if (node->bal == 0) {
				node->bal = 1;
			}
			else { // p->bal == 1
				// Балансировка
				TreeNode* p1 = node->right;
				if (p1->bal == 1) {
					// Малый левый поворот
					node->right = p1->left;
					p1->left = node;
					node->bal = 0;
					node = p1;
				}
				else {
					// Большой левый поворот
					TreeNode* p2 = p1->left;
					p1->left = p2->right;
					p2->right = p1;
					node->right = p2->left;
					p2->left = node;
					node->bal = (p2->bal == 1) ? -1 : 0;
					p1->bal = (p2->bal == -1) ? 1 : 0;
					node = p2;
				}
				node->bal = 0;
				h = false;
			}
		}
	}
}
void balanceL(TreeNode*& p, bool& h) {
	if (p->bal == -1) {
		// Если левое поддерево уменьшилось, и баланс был -1, то баланс становится 0
		p->bal = 0;
	}
	else if (p->bal == 0) {
		// Если баланс был 0, то баланс становится +1, и высота дерева больше не меняется
		p->bal = 1;
		h = false;
	}
	else { // p->bal == 1
		TreeNode* p1 = p->right;
		if (p1->bal >= 0) {
			// Правый поворот или малый левый поворот
			p->right = p1->left;
			p1->left = p;
			if (p1->bal == 0) {
				p->bal = 1;
				p1->bal = -1;
				h = false;
			}
			else {
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else {
			// Большой левый поворот
			TreeNode* p2 = p1->left;
			p1->left = p2->right;
			p2->right = p1;
			p->right = p2->left;
			p2->left = p;
			p->bal = (p2->bal == 1) ? -1 : 0;
			p1->bal = (p2->bal == -1) ? 1 : 0;
			p2->bal = 0;
			p = p2;
		}
	}
}

void balanceR(TreeNode*& p, bool& h) {
	if (p->bal == 1) {
		// Если правое поддерево уменьшилось, и баланс был +1, то баланс становится 0
		p->bal = 0;
	}
	else if (p->bal == 0) {
		// Если баланс был 0, то баланс становится -1, и высота дерева больше не меняется
		p->bal = -1;
		h = false;
	}
	else { // p->bal == -1
		TreeNode* p1 = p->left;
		if (p1->bal <= 0) {
			// Левый поворот или малый правый поворот
			p->left = p1->right;
			p1->right = p;
			if (p1->bal == 0) {
				p->bal = -1;
				p1->bal = 1;
				h = false;
			}
			else {
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else {
			// Большой правый поворот
			TreeNode* p2 = p1->right;
			p1->right = p2->left;
			p2->left = p1;
			p->left = p2->right;
			p2->right = p;
			p->bal = (p2->bal == -1) ? 1 : 0;
			p1->bal = (p2->bal == 1) ? -1 : 0;
			p2->bal = 0;
			p = p2;
		}
	}
}

void deleteNode(TreeNode*& p, GovNumber key, bool& h) {
	if (p == nullptr) {
		h = false; // Узел не найден
		return;
	}

	if (key < p->gn) {
		// Ищем ключ в левом поддереве
		deleteNode(p->left, key, h);
		if (h) balanceR(p, h); // Балансируем правое поддерево
	}
	else if (key > p->gn) {
		// Ищем ключ в правом поддереве
		deleteNode(p->right, key, h);
		if (h) balanceL(p, h); // Балансируем левое поддерево
	}
	else {
		// Найден узел для удаления
		if (p->left == nullptr || p->right == nullptr) {
			// У узла один или ноль потомков
			TreeNode* temp = p;
			p = (p->left != nullptr) ? p->left : p->right;
			delete temp;
			h = true; // Высота поддерева уменьшилась
		}
		else {
			// У узла два потомка
			TreeNode* minNode = p->right;
			while (minNode->left != nullptr) {
				minNode = minNode->left; // Находим минимальный узел в правом поддереве
			}
			p->gn = minNode->gn; // Заменяем ключ текущего узла
			deleteNode(p->right, minNode->gn, h); // Удаляем узел-замену
			if (h) balanceL(p, h); // Балансируем левое поддерево
		}
	}
}


void print(TreeNode* node, int depth = 0) {
	if (node != nullptr) {
		print(node->right, depth + 1);
		cout << string(depth * 4, ' ') << node->gn.letter <<node->gn.data << node->gn.word << " (bal=" << node->bal << ")" << endl;
		print(node->left, depth + 1);
	}
}

	const void dirpass(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->gn.letter << node->gn.data << node->gn.word << endl;
		dirpass(node->left);
		dirpass(node->right);
	}
int main() {
	List list;
	vector<GovNumber> fileName;
	fstream fin;
	fin.open("avl1.txt", fstream::in);
	GovNumber temp;
	while (fin >> temp.letter >> temp.data >> temp.word) {
		fileName.push_back(temp);
	}
	TreeNode* root = nullptr;
	bool h = false;
	for (int i = 0;i < fileName.size(); i++) {
		tree_insert(root, fileName[i], h, list);
	}
	print(root);
	dirpass(root);
	list.print1();
	deleteNode(root, fileName[1], h);
	dirpass(root);
	print(root);
	return 0;
}