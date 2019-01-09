/*
 * client.cpp
 *
 *  Created on: 04-Fan-2019
 *      Author: Parth shah
 */

#include <iostream>

#include "ToyFactory.cpp"

using namespace std;

int main() {
	int type;
	while (1) {
		cout << endl
				<< "Enter the value \n 0: Exit \n 1: Car \n 2: Bike \n 3: Plane "
				<< endl;
		cin >> type;
		if (type <= 0) {
			break;
		}
		Toy *toy = NULL;
		toy = ToyFactory::create(type);
		if (toy) {
			toy->showProduct();
			delete toy;
		}

	}
	return 0;
}

