/*
 * singletonClass.cpp
 *
 *  Created on: 30-Oct-2018
 *      Author: Parth shah
 */

#include <iostream>

using namespace std;

class singleton {
private:
	static singleton* sg;
	int data;
	singleton() {
		data = 0;
	}
	void operator =(const singleton& s1) {

	}
	singleton(const singleton& s1) {
	}

public:
	static singleton *getInstance() {
		if (sg == NULL) {
			sg = new singleton();
		}
		return sg;
	}
	void setdata(int val) {
		data = val;
	}
	int getdata() {
		cout << data << endl;
	}
};

singleton* singleton::sg = NULL;

int main() {
	singleton* s1 = s1->getInstance();
	s1->getdata();
	s1->setdata(200);
	s1->getdata();
	return 0;
}

