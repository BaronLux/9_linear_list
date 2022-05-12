#include <chrono>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
class Appl {
public:
	static int globnmbr;
	int priority = 0;
	int number;
	float time = 0;
	bool state = false;
	Appl(int p) {
		priority = p;
		Appl::globnmbr++;
		number = Appl::globnmbr;
	}
};
int Appl::globnmbr = 0;
auto start = chrono::high_resolution_clock::now();
class Stack {
public:
	vector<Appl*> lst;
	int maxsize;
	Stack(int size) {
		maxsize = size;
	}
	void ServePriority(int priority) {
		if (priority > 4 || priority < 1)
			return;
		for (int i = 0; i < maxsize; i++)
		{
			if (lst[i]->priority == priority && lst[i]->state == false) {
				lst[i]->state = true;
				auto finish = chrono::high_resolution_clock::now();
				lst[i]->time = (float)(((chrono::duration_cast<chrono::microseconds>)
								(finish - start)).count()) / 60000000;
			}
		}
	}
	void Push(Appl *i) {
		if (cursize <= maxsize) {
			lst.push_back(i);
			cursize++;
		}
	}
	void Pop() {
		if (cursize != 0) {
			lst.pop_back();
			cursize--;
		}
	}
	bool IsEmpty() {
		return cursize == 0;
	}
private:
	int cursize = 0;
};

int main()
{
	setlocale(0, "");
	srand((unsigned)time(NULL));
	int maxsize, newel;
	cin >> maxsize;
	auto st = new Stack(maxsize);
	for (int i = 0; i < maxsize; i++)
	{
		//cin >> newel;
		st->Push(new Appl(rand() % 3 + 1));
	}
	for (auto& j : st->lst) {
		cout << "priority=" << j->priority 
			<< "\nnumber=" << j->number << "\n";
	}
	cout << "\n---------------------------------------\n";
	st->ServePriority(1);
	st->ServePriority(2);
	st->ServePriority(3);
	for (auto& j : st->lst) {
		cout << "priority=" << j->priority 
			<< "\nnumber=" << j->number 
			<< "\nelapsed time=" << j->time << " ms\n";
	}
}