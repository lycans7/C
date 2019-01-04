/*
 * Inheritance.cpp
 *
 *  Created on: 03-Jan-2019
 *      Author: Parth shah
 */

#include <iostream>

using namespace std;

class A {

private:
	int a;
public:
	void setval(int val) {
		this->a = val;
	}
	void getval() {
		cout << this->a << endl;
	}
};

class B: public A {
public:
	int a;
	void setA(int val) {
			this->a = val;
	}
	void setB(int val) {
		setval(val);
	}
	void print(){
		cout << this->a << endl;
		getval();
	}

};

int main() {
	A a;
	a.setval(20);
	a.getval();
	B b;
	b.setA(20);
	b.setB(30);
	b.print();

	return 0;
}

