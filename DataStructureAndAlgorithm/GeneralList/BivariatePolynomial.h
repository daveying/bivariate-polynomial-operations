#pragma once
#include <string>
#include <vector>
using namespace std;

struct MonadicPolynomialNode
{
	MonadicPolynomialNode(double coefficient, int order) :coefficient_(coefficient), order_(order), next_(0) {};
	MonadicPolynomialNode(const MonadicPolynomialNode &another) { this->coefficient_ = another.coefficient_; this->order_ = another.order_; this->next_ = 0; }
	double coefficient_;
	int order_;
	MonadicPolynomialNode *next_;

	bool operator<(const MonadicPolynomialNode &second);
	bool operator>(const MonadicPolynomialNode &second);
	bool operator==(const MonadicPolynomialNode &second);
private:
	//if order of first > order of second, return  1
	//if order of first < order of second, return -1
	//if order of first = order of second, return  0
	int Compare(const MonadicPolynomialNode &first, const MonadicPolynomialNode &second);
};

class MonadicPolynomial
{
public:
	MonadicPolynomial() :monadicPolynomail_(0) { variableName_ = "x"; };
	MonadicPolynomial(string variableName) :monadicPolynomail_(0), variableName_(variableName) {}
	MonadicPolynomial(vector<MonadicPolynomialNode> nodes, string name = "x");
	MonadicPolynomial(const MonadicPolynomial &another);
	~MonadicPolynomial();
	void SetVariableName(string name) { this->variableName_ = name; }
	void Print(bool flag = true);
	void Add(const MonadicPolynomial &another);
	void Inverse();
	void Substract(const MonadicPolynomial & another);
	
private:
	MonadicPolynomialNode *monadicPolynomail_;
	string variableName_;
	void EraseZeroItem();
	void Insert(const MonadicPolynomialNode &node);
	void PrintNode(const MonadicPolynomialNode &node, bool first = false);
	
};

struct BivariatePolynomialNode
{
	BivariatePolynomialNode(MonadicPolynomial coefficient, int order) :coefficient_() {}
	MonadicPolynomial coefficient_;
	int order_;
	BivariatePolynomialNode *next_;

	bool operator<(const BivariatePolynomialNode &second);
	bool operator>(const BivariatePolynomialNode &second);
	bool operator==(const BivariatePolynomialNode &second);
private:
	//if order of first > order of second, return  1
	//if order of first < order of second, return -1
	//if order of first = order of second, return  0
	int Compare(const BivariatePolynomialNode &first, const BivariatePolynomialNode &second);
};

class BivariatePolynomial
{
public:
	BivariatePolynomial() :bivariatePolynomial_(0) { variableName_ = "x"; };
	BivariatePolynomial(string variableName) :bivariatePolynomial_(0), variableName_(variableName){}
private:
	BivariatePolynomialNode *bivariatePolynomial_;

	string variableName_;
};