#pragma once
#include "MonadicPolynomial.h"
#include "PolynomialNode.h"
using namespace std;

class BivariatePolynomialNode : public PolynomialNode
{
public:
	MonadicPolynomial coefficient;
	BivariatePolynomialNode *next;
	BivariatePolynomialNode(MonadicPolynomial &nodeCoefficient, int nodeOrder) :PolynomialNode(nodeOrder), coefficient(nodeCoefficient), next(0) {}
};