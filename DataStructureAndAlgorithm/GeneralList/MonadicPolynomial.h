#pragma once
#include <string>
#include <vector>

#include "PolynomialNode.h"
#include "MonadicPolynomialNode.h"
using namespace std;


class MonadicPolynomial
{
public:
	//construction function, create a defualt monadic polynomial instance, which has no monadic polynomial node.
	MonadicPolynomial() :monadicPolynomial_(0) { variableName_ = "x"; };

	//construction function, sepcify the variable name like x y or any other names.
	MonadicPolynomial(string variableName) :monadicPolynomial_(0), variableName_(variableName) {}

	//construction function, create a monadic polynomial instance with a MonadicPolynomialNode vector.
	//you don't need to provide sorted nodes
	MonadicPolynomial(vector<MonadicPolynomialNode> nodes, string name = "x");

	//copy construction function, copy another monadic polynomial.
	MonadicPolynomial(const MonadicPolynomial &another);

	//deconstruction function, free the memory of each node
	~MonadicPolynomial();

	//set variable name, the default value is "x", so when print out, it will look like this: x^6 + 3x^3 + 3
	void SetVariableName(string name) { this->variableName_ = name; }

	//print the monadic polynomial on screen
	void Print(bool flag = true);

	//add another monadic polynomial to this monadic polynomial.
	void Add(const MonadicPolynomial &another);

	//inverse this polynomial. if this polynomial is x^4 - 3x^2, Inverse() will make this polynomial to -x^4 + 3x^2
	void Inverse();

	//substruct another monadic polynomial from this mondiac polynomial
	void Substract(const MonadicPolynomial &another);
	
private:
	MonadicPolynomialNode *monadicPolynomial_;	//head of monadic polynomail nodes
	string variableName_;						//variable name of this polynomial like x, y, or something else

	//when create a new monadic polynomial with a set of nodes or when perform add/substruct operation, 
	//there will have chances to get item with zero coefficient, so we should to clean these item out of list.
	void EraseZeroItem();

	//insert a new monadic polynomial node into this monadic polynomial list. 
	//we should insert new item to right place or merge to original node to keep bigger order come first.
	void Insert(const MonadicPolynomialNode &node);

	//print a node of monadic polynomial.
	//TODO this method should move to class MondicPolynomialNode
	void PrintNode(const MonadicPolynomialNode &node, bool first = false);
	
};


