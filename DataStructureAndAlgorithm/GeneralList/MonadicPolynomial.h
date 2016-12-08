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
	MonadicPolynomial(const MonadicPolynomial &another);
	~MonadicPolynomial();
	void SetVariableName(string name) { this->variableName_ = name; }
	void Print(bool flag = true);
	void Add(const MonadicPolynomial &another);
	void Inverse();
	void Substract(const MonadicPolynomial & another);
	
private:
	MonadicPolynomialNode *monadicPolynomial_;
	string variableName_;
	void EraseZeroItem();
	void Insert(const MonadicPolynomialNode &node);
	void PrintNode(const MonadicPolynomialNode &node, bool first = false);
	
};


