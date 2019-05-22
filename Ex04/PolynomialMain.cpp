/**
 *
 *
 */

#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <synchapi.h>
#endif

#include "Polynomial.h"
#include "Integer.h"

using namespace std;

int main(int argc, char* argv[]) {
#ifdef _WIN32
	Sleep(2000);
#endif

	// variable names and exponent vectors ("power products")
	string vars[2] = { "x", "y" };
	int e1[2] = { 1,2 }; int e2[2] = { 2,1 }; int e3[2] = { 1,0 };
	int e4[2] = { 0,1 }; int e5[2] = { 0,0 }; int e6[2] = { 2,2 };

	// construct polynomials p and q in two variables
	Polynomial* p = new Polynomial(2, vars);
	p->add(new Integer(3), e1).add(new Integer(5), e2).add(new Integer(7), e3)
		.add(new Integer(11), e4).add(new Integer(13), e5);
	Polynomial* q = new Polynomial(2, vars);
	q->add(new Integer(11), e4).add(new Integer(-3), e2).add(new Integer(2), e6)
		.add(new Integer(-2), e2);
	// print p and q
	cout << p->str() << endl << q->str() << endl;
	// set p to p+2*q and print it
	Polynomial* r = p->operator+(q)->operator+(q);
	cout << r->str() << endl;

	delete p;
	delete q;
	//delete r;

#ifdef _WIN32
	Sleep(2000);
#endif
	return 0;
}
