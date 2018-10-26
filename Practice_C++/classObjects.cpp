/*
 * classObjects.cpp
 *
 *  Created on: 15-Oct-2018
 *      Author: Parth shah
 */

#include <iostream>


using namespace std;

class box {
	int a;
public:
	// constructor ,copy constructor and assigning operator is created by compiler if it is not created by user.
	int def();						// declaration
	box() {							//constructor
		this->a = def();
	}

	box(int a) {					// parameterized constructor created by user only.
		this->a = a;
	}

	box(box &box1) { 					//copy constructor
		this->a = box1.a;
	}

	void insert(int a) {				//user defined function
		this->a = a;
	}
	void display() {						//user defined function
		cout << a <<"\t"<< endl;
	}
	void operator = (const box &box1){		//Assigning operator
		if(this != &box1)
		this->a = box1.a;
	}

	void operator +(box &b1){        //operator overloading
		this->a = this->a + b1.a ;
	}
	box operator -(box const &b1){        // returning object operator overloading
		box b2;
		b2.a = a - b1.a;
		return b2;
	}
};

int box::def() {			//  definition using scope resolution operator
	return 0;
}
int main() {

	box b1;
	b1.display();
	b1.insert(8);
	b1.display();
	box b2(5);
	b2.display();
	box b3(b1);
	b3.display();
	b3=b2;
	b3.display();
	b3+b1;
	b3.display();
	b3.operator +(b1);
	b3.display();
	b3 = b1-b2;// example with multiple
	b3.display();
	b3 = b1-(b2-b3);// example with multiple
	b3.display();
	return 0;
}

