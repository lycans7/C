/*
 * ToyFactory.cpp
 *
 *  Created on: 04-Jan-2019
 *      Author: Parth shah
 */

#ifndef _ToyFactory_cpp
#define _ToyFactory_cpp

#include "ObjectClass.cpp"

class ToyFactory {
public:
	static Toy* create(int key) {
		Toy* t = NULL;
		switch (key) {
			case 1: {
				t = new car();
				break;
			}
			case 2: {
				t = new Bike();
				break;
			}
			case 3: {
				t = new Plane();
				break;
			}
			default: {
				cout << " Invalid value " << endl;
			}
		}
		t->PreparePart();
		t->combinePart();
		t->assemblePart();
		t->applyLabel();
		return t;
	}

};

#endif

