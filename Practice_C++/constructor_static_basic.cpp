#include <iostream>
#include <stdio.h>
using namespace std;
 
/*
class A{
public:
	A(){
		printf("A");
	}
	~A(){

		printf("\n D A");
	}
};
class b : public A {
public:
	b(){
		printf("b");
	}
	~b(){

		printf(" \n D b");
	}

};
class c : public b,public A{
	public:
		c(){
			printf("c");

		}
		~c(){
			printf(" \n D c");
		}

};

class d: public c, public b,public A{
	public:
		d(){
			printf("d");

		}
		~d(){
			printf(" \n D d" );
		}

};
int main(){

	d dd;
	return 0;
}*/
/* output: constructor := AbAcAbAd
	   Destructor := dAbAcAbA  */


/*

class A{
public:
static int a;
	A(){
	a = 6;
	}	
	static void get(){

		cout<<a<<endl;
	}

};

int A::a = 5;

int main(){
	A a;
	a.get();
	A b;
	b.get();
	A::get();


	return 0;
}*/



class super{
	public:
		super();
		super(int a,int b){
			cout<< "super  "<<a<<b<<endl;
		}

		~super(){

			cout<<"super dis"<<endl;
		}
};


class base : public super{
	public:
		base(int a, int b):super(a,b){
			cout<<"base  "<<a<<b<<endl;
		}
		~base(){
			cout<<"base dis"<<endl;
		}
};


class base1 : public base,public super{
	public:
		base1(int a,int b):base(9,10),super(13,14){
			cout<<"base1  "<<a<<b<<endl;
		}

		~base1(){
			cout<<"base1 dis"<<endl;
		}
};

int main(){
	base1 bs(4,5);

	return 0;
}
