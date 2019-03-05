#include <iostream>
#include <thread>
#include <stdlib.h>

using namespace std;

void fun() {
	cout << " Hello World " << endl;
}

int main() {

	thread t1(fun); // t1 start running.

//	t1.join(); // main thread wait for t1 to finish.
	t1.detach(); // t1 freely of it own , i.e. t1 is daemon process , so
				//run time library is responsible for to retrieve this thread.
	printf(" %d ",__LINE__);
//	t1.join();
	if (t1.joinable()){
		t1.join();
	}


	return 0;

}
