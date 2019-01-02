/*
 * ReferenceVariable.cpp
 *
 *  Created on: 29-Oct-2018
 *      Author: Parth shah
 */

/******************************************************************************************************
 1)Reference is a address, reference variable is a internal pointer, declaration of reference variable
 is preceded with '&' symbol (don't read as address of.)
 2)Reference variable must be initialized during declaration.
 3)It can be initialized with already declared variable only.
 4)Reference variable cannot be updated to another address.
 5)both case it will work , variable if declare only or with declare + define
********************************************************************************************************/
#include <iostream>

using namespace std;

int main() {
	int val;
	int &ref_var = val;			//reference variable
	cin >> val;
	cout << val << "\t" << ref_var << endl;
	val++;
	cout << val << "\t" << ref_var << endl;
	ref_var++;
	cout << val << "\t" << ref_var << endl;
	return 0;
}

