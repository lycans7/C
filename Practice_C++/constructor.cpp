/*
 * constructor.cpp
 *
 *  Created on: 08-Jan-2019
 *      Author: Parth shah
 */

#include <iostream>

using namespace std;

class parent {
private:
	int a, b;
public:
	parent() {
	}
	parent(int x, int y) :
			a(x), b(y) {
	}
	void Display() {
		cout << "Parent class :" << a <<"\t"<< b << endl;
	}
};

class parent1 {
private:
	int val, val1;
	parent abc;
public:
	parent1() {
	}
	parent1(int q, int w, int e, int r) :
			val(q), val1(w), abc(e, r) {
	}
	void Display() {
		cout << "Parent1 class :" << val <<"\t"<< val1 << endl;
		abc.Display();
	}
};

int main() {
	parent1 p(1, 2, 3, 4);
	p.Display();
	return 0;
}
