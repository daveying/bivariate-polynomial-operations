#pragma once
#include "PolynomialNode.h"
using namespace std;

class MonadicPolynomialNode : public PolynomialNode
{
public:
	double coefficient;
	MonadicPolynomialNode *next;
	MonadicPolynomialNode(double nodeCoefficient, int nodeOrder) :PolynomialNode(nodeOrder), coefficient(nodeCoefficient), next(0) {	}
	MonadicPolynomialNode(const MonadicPolynomialNode &another) :PolynomialNode(another.order) { this->coefficient = another.coefficient; this->next = 0; }
};