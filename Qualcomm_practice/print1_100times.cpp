/*
 * print1_100times.cpp
 *
 *  Created on: 27-Nov-2018
 *      Author: Parth shah
 */

#include <iostream>

using namespace std;
// CPP program to print "1" 100 times.
int c = 0;
// Prints 1 only once
#define a cout<<"1"<<endl<<c++;

// Puts "a" 10 times
#define b a a a a a a a a a a

// Puts "b" 10 times
#define c b b b b b b b b b b

int main()
{
  c;
  return 0;
}
