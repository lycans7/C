/*
 * Chain_of_Responsibility.cpp
 *
 *  Created on: 03-Jan-2019
 *      Author: Parth shah
 */

#include <iostream>
#include <stdio.h>

using namespace std;

class Handler {
protected:
	Handler *next;
public:
	Handler() {
		next = NULL;
	}
	virtual ~Handler() {

	}
	virtual void request(int val) = 0;

	void setHandler(Handler* nextHandler) {
		next = nextHandler;
	}

};

class specialHandler: public Handler {
private:
	int myLimit, myId;
public:
	specialHandler(int Limit, int Id) {
		this->myId = Id;
		this->myLimit = Limit;
	}
	~specialHandler() {
	}

	void request(int val) {
		printf(" %d ",__LINE__);
		if (val < myLimit) {
			cout << "Handler " << myId
					<< " handled the request with a limit of " << myLimit
					<< endl;
			printf(" %d ",__LINE__);
		} else if (next != NULL) {
			next->request(val);
			cout<<"Hello"<<endl;
			printf(" %d ",__LINE__);
		} else {
			cout << "Sorry, I am the last handler (" << myId
					<< ") and I can't handle the request." << endl;
		}
		printf(" %d ",__LINE__);
	}
};

int main() {
	Handler *h1 = new specialHandler(10, 1);
	Handler *h2 = new specialHandler(20, 2);
	Handler *h3 = new specialHandler(30, 3);

	h1->setHandler(h2);
	printf(" %d ",__LINE__);
	h1->setHandler(h3);
	printf(" %d ",__LINE__);
//	h2->setHandler(h3);
	printf(" %d ",__LINE__);
	h1->request(18);
	printf(" %d ",__LINE__);
	h1->request(20);
	printf(" %d ",__LINE__);
	h1->request(40);

	printf(" %d ",__LINE__);
	delete h1;
	delete h2;
	delete h3;

	return 0;
}

