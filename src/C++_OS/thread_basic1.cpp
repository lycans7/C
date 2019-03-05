/*
 * thread_basic1.cpp
 *
 *  Created on: 22-Jan-2019
 *      Author: Parth shah
 */

#include <iostream>
using namespace std;

void fun() {
	cout << "Hello world" << endl;
}

int main() {
	thread t1(fun);

	for (int i = 0; i < 100; i++) {
		cout << " main:" << i;

	}
	t1.join();
	return 0;
}
