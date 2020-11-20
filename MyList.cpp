#include "MyList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Date {
	int D;
	int M;
	int Y;
};

class Data {
public:
	string catalogueName;
	string fileName;
	string specification;
	Date date;
	int size;
	friend ifstream& operator>> (ifstream& inf, Data& data) {
		Data tmp;
		if (inf.peek() != -1) {
			inf >> tmp.catalogueName;
			inf >> tmp.fileName;
			inf >> tmp.specification;
			inf >> tmp.date.D;
			inf >> tmp.date.M;
			inf >> tmp.date.Y;
			inf >> tmp.size;
		}
		else
			return inf;
		data = tmp;
		return inf;
	}
};

struct Node
{
	Data data;
	Node* next;
};

typedef Node* TList;

void init(TList& head)
{
	head = NULL;
}

bool isEmpty(TList head)
{
	return head == NULL;
}

void addToHead(TList& head, Data elem)
{
	TList p = new Node;
	p->data = elem;
	p->next = head;
	head = p;
}

void addAfterNode(TList pNode, Data elem)
{
	TList p = new Node;
	p->data = elem;
	p->next = pNode->next;
	pNode->next = p;
}

void deleteFromHead(TList& head)
{
	TList p = head;
	head = head->next;
	p->next = 0;
	delete p;
}

void deleteAfterNode(TList pNode)
{
	if (pNode != 0)
	{
		TList p = pNode->next;
		pNode->next = p->next;
		p->next = 0;
		delete p;
	}
}

void clear(TList& head)
{
	while (!isEmpty(head))
		deleteFromHead(head);
	delete head;
}

void printList(TList head)
{
	TList p = head;
	while (p != NULL)
	{
		cout << p->data.catalogueName << endl;
		cout << p->data.fileName << endl;
		cout << p->data.specification << endl;
		cout << p->data.date.D << endl;
		cout << p->data.date.M << endl;
		cout << p->data.date.Y << endl;
		cout << p->data.size << endl;
		p = p->next;
	}
}

bool fromFileToList(TList& head) {
	ifstream inf("List.txt");
	if (!inf.is_open()) {
		cout << "Не удалось считать файл";
		return 0;
	}
	init(head);
	TList tail = head;
	for (Data current; inf >> current;) {
		if (isEmpty(head))
		{
			addToHead(head, current);
			tail = head;
		}
		else
		{
			addAfterNode(tail, current);
			tail = tail->next;
		}
	}
		
}

void findNamesOnCat(TList& head) {
	TList pNode = head; TList qNode; // Создаём 2 указателя
	while (pNode != NULL) { // Проходимся по списку
		if ((pNode->data.specification == ".cpp") || (pNode->data.specification == ".h")) { // Если находим файл .cpp или .h
			qNode = pNode->next; // Указатель ставим на следующий элемент списка
			while ((qNode != NULL) && (qNode->data.catalogueName == pNode->data.catalogueName)) {
				if (pNode->data.fileName == qNode->data.fileName) {
					if (((pNode->data.specification == ".cpp") && (qNode->data.specification == ".h")) || ((qNode->data.specification == ".cpp") && (pNode->data.specification == ".h"))) {
						cout << pNode->data.catalogueName << "->" << pNode->data.fileName << endl;
					}
				}
				qNode = qNode->next;
			}
		}
		pNode = pNode->next;
	}
}