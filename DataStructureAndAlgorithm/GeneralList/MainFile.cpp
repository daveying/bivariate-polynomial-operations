#include "MonadicPolynomial.h"
#include "MonadicPolynomialNode.h"
#include "BivariatePolynomial.h"
#include "BivariatePolynomialNode.h"
#include <iostream>
using namespace std;

int main()
{
	MonadicPolynomialNode n1(3, 5);
	MonadicPolynomialNode n2(4, 4);
	MonadicPolynomialNode n3(-1, 3);
	MonadicPolynomialNode n4(2, 1);
	MonadicPolynomialNode n5(-1, 0);

	MonadicPolynomialNode n6(2, 4);
	MonadicPolynomialNode n7(1, 3);
	MonadicPolynomialNode n8(-7, 2);
	MonadicPolynomialNode n9(1, 1);
	vector<MonadicPolynomialNode> nodes1, nodes2;
	nodes1.push_back(n1);
	nodes1.push_back(n2);
	nodes1.push_back(n3);
	nodes1.push_back(n4);
	nodes1.push_back(n5);


	nodes2.push_back(n9);
	nodes2.push_back(n6);
	nodes2.push_back(n7);
	nodes2.push_back(n8);

	MonadicPolynomial m1(nodes1);
	MonadicPolynomial m2(nodes2);
	cout << "original m1: ";
	m1.Print();
	cout << "original m2: ";
	m2.Print();
	//m2.Inverse();
	//cout << "Inversed m2: ";
	//m2.Print();
	m2.Add(m1);
	cout << "m2 + m1: ";
	m2.Print();
	m2.Substract(m1);
	cout << "m2 - m1: ";
	m2.Print();

	return 0;
}