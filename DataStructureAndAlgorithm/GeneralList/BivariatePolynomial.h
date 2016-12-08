#pragma once
#include <string>

#include "BivariatePolynomialNode.h"
using namespace std;

class BivariatePolynomial
{
public:
	BivariatePolynomial() :bivariatePolynomial_(0) { variableName_ = "x"; };
	BivariatePolynomial(string variableName) :bivariatePolynomial_(0), variableName_(variableName){}
private:
	BivariatePolynomialNode *bivariatePolynomial_;

	string variableName_;
};
