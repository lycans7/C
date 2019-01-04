/*
 * ObjectClass.cpp
 *
 *  Created on: 04-Jan-2019
 *      Author: Parth shah
 */

#ifndef ObjectClass.cpp
#define ObjectClass.cpp

#include <iostream>
#include <string>

using namespace std;

class Toy {
protected:
	string name;
	float price;
public:
	virtual void PreparePart() = 0;
	virtual void combinePart() = 0;
	virtual void assemblePart() = 0;
	virtual void applyLabel() = 0;
	virtual void showProduct() = 0;
};

class car: public Toy {

public:
	name = "Car";price = 20;
	void PreparePart() {
		cout << " Preparing Part" << endl;
	}
	void combinePart() {
		cout << " combine Part" << endl;
	}
	void assemblePart() {
		cout << " assemble Part" << endl;
	}
	void applyLabel() {
		cout << " apply Label" << endl;
	}
	void showProduct() {
		cout << " Product name " << name << endl << " Cost " << price << endl;
	}
};

class Bike: public Toy {

public:
	name = "Bike";price = 200;
	void PreparePart() {
		cout << " Preparing Part" << endl;
	}
	void combinePart() {
		cout << " combine Part" << endl;
	}
	void assemblePart() {
		cout << " assemble Part" << endl;
	}
	void applyLabel() {
		cout << " apply Label" << endl;
	}
	void showProduct() {
		cout << " Product name " << name << endl << " Cost " << price << endl;
	}
};

class Plane: public Toy {

public:
	name = "Plane";price = 2000;
	void PreparePart() {
		cout << " Preparing Part" << endl;
	}
	void combinePart() {
		cout << " combine Part" << endl;
	}
	void assemblePart() {
		cout << " assemble Part" << endl;
	}
	void applyLabel() {
		cout << " apply Label" << endl;
	}
	void showProduct() {
		cout << " Product name " << name << endl << " Cost " << price << endl;
	}
};

#endif
