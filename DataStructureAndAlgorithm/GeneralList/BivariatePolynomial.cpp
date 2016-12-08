#include "BivariatePolynomial.h"
#include <bitset>
#include <algorithm>
#include <iostream>
using namespace std;

//########################## MonadicPolynomial #####################//

void MonadicPolynomial::Inverse()
{
	MonadicPolynomialNode *ptr = this->monadicPolynomail_;
	while (ptr != 0)
	{
		ptr->coefficient_ = -ptr->coefficient_;
		ptr = ptr->next_;
	}
}

void MonadicPolynomial::EraseZeroItem()
{
	MonadicPolynomialNode *ptr1 = this->monadicPolynomail_;
	if (this->monadicPolynomail_ == 0) // no node
		return;
	if (ptr1->next_ == 0) // just one node
	{
		if (ptr1->coefficient_ > 0 || ptr1->coefficient_ < 0);
		else
		{
			ptr1->order_ = 0;
			return;
		}
	}

	MonadicPolynomialNode *fakeHead = new MonadicPolynomialNode(0, 0);
	fakeHead->next_ = this->monadicPolynomail_;
	ptr1 = fakeHead;
	MonadicPolynomialNode *ptr2 = this->monadicPolynomail_;
	while (ptr2 != 0)
	{
		if (ptr2->coefficient_ > 0 || ptr2->coefficient_ < 0)
		{
			ptr1 = ptr1->next_;
			ptr2 = ptr2->next_;
		}
		else
		{
			ptr1->next_ = ptr2->next_;
			MonadicPolynomialNode *temp = ptr2;
			ptr2 = ptr2->next_;
			delete temp;
		}
	}
	this->monadicPolynomail_ = fakeHead->next_;
	delete fakeHead;
}

void MonadicPolynomial::Insert(const MonadicPolynomialNode &node)
{
	MonadicPolynomialNode *head = this->monadicPolynomail_, *ptr = this->monadicPolynomail_;
	MonadicPolynomialNode *ptrNode = new MonadicPolynomialNode(node.coefficient_, node.order_);
	if (head == 0)
	{
		this->monadicPolynomail_ = ptrNode;
		return;
	}
	if (ptr->next_ == 0) // this->monadicPolynomial_ just has one node
	{
		if (node.order_ > head->order_) // new node is greater than former one
		{
			head = ptrNode;
			head->next_ = this->monadicPolynomail_;
			this->monadicPolynomail_ = head;
			return;
		}
		if (node.order_ == head->order_) // new node is equal with former one
		{
			head->coefficient_ += node.coefficient_;
			if (head->coefficient_ == 0)
				head->order_ = 0;
			return;
		}
		if (node.order_ < head->order_)
		{
			head->next_ = ptrNode;
			return;
		}
			
	}

	while (ptr->next_ != 0)
	{
		if (node.order_ > ptr->order_)
		{
			ptrNode->next_ = head;
			head = ptrNode;
			this->monadicPolynomail_ = head;
			return;
		}
		if (node.order_ == ptr->order_)
		{
			ptr->coefficient_ += node.coefficient_;
			return;
		}
		if (node.order_ < ptr->order_ && node.order_ > ptr->next_->order_)
		{
			ptrNode->next_ = ptr->next_;
			ptr->next_ = ptrNode;
			return;
		}
		if (node.order_ == ptr->next_->order_)
		{
			ptr->next_->coefficient_ += node.coefficient_;
			return;
		}
		ptr = ptr->next_;
	}
	ptr->next_ = ptrNode;
}

void MonadicPolynomial::Add(const MonadicPolynomial &another)
{
	MonadicPolynomialNode *ptr = another.monadicPolynomail_;
	while (ptr != 0)
	{
		this->Insert(*ptr);
		ptr = ptr->next_;
	}
	this->EraseZeroItem();
}

void MonadicPolynomial::Substract(const MonadicPolynomial &another)
{
	MonadicPolynomial temp(another);
	temp.Inverse();
	this->Add(temp);
}

MonadicPolynomial::MonadicPolynomial(vector<MonadicPolynomialNode> nodes, string name)
{
	variableName_ = name;
	if (nodes.size() == 0)
	{
		this->monadicPolynomail_ = 0;
		return;
	}
	
	sort(nodes.begin(), nodes.end());
	
	MonadicPolynomialNode *ptr = 0;
	bool first = true;
	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		if (nodes[i].coefficient_ > 0 || nodes[i].coefficient_ < 0)
		{
			if (first)
			{
				first = false;
				this->monadicPolynomail_ = new MonadicPolynomialNode(nodes[i].coefficient_, nodes[i].order_);
				ptr = this->monadicPolynomail_;
			}
			else
			{
				ptr->next_ = new MonadicPolynomialNode(nodes[i].coefficient_, nodes[i].order_);
				ptr = ptr->next_;
			}
		}
	}
	ptr->next_ = 0;

	ptr = this->monadicPolynomail_;
	MonadicPolynomialNode *ptr2 = this->monadicPolynomail_->next_;
	while (ptr2 != 0)
	{
		if (*ptr == *ptr2)
		{
			MonadicPolynomialNode *temp = ptr2;
			ptr->next_ = temp->next_;
			ptr->coefficient_ += temp->coefficient_; //merge two items
			ptr2 = temp->next_; // ptr2 move a step back, while ptr shouldn't move
			delete temp;
		}
		else
		{
			ptr = ptr->next_;
			ptr2 = ptr2->next_;
		}
	}
}

MonadicPolynomial::MonadicPolynomial(const MonadicPolynomial &another)
{
	if (another.monadicPolynomail_ == 0)
	{
		this->monadicPolynomail_ = 0;
		this->variableName_ = another.variableName_;
		return;
	}
	MonadicPolynomialNode *ptr = another.monadicPolynomail_;
	MonadicPolynomialNode *thisPtr = 0, *head = 0;
	head = new MonadicPolynomialNode(ptr->coefficient_, ptr->order_);
	ptr = ptr->next_;
	thisPtr = head;
	while (ptr != 0)
	{
		thisPtr->next_ = new MonadicPolynomialNode(ptr->coefficient_, ptr->order_);
		ptr = ptr->next_;
		thisPtr = thisPtr->next_;
	}
	this->monadicPolynomail_ = head;
}

MonadicPolynomial::~MonadicPolynomial()
{
	MonadicPolynomialNode *temp, *ptr;
	temp = this->monadicPolynomail_;
	this->monadicPolynomail_ = 0;
	ptr = temp->next_;
	while (ptr != 0)
	{
		delete temp;
		temp = ptr;
		ptr = ptr->next_;
	}
	delete temp;
}

void MonadicPolynomial::PrintNode(const MonadicPolynomialNode &node, bool first)
{
	if (first)
	{
		if (node.coefficient_ > 0 && node.coefficient_ != 1.0)
			std::cout << node.coefficient_;
		if (node.coefficient_ < 0 && node.coefficient_ != -1.0)
			std::cout << node.coefficient_;
		if (node.coefficient_ == -1.0)
			std::cout << "-";
	}
	else
	{
		if (node.coefficient_ > 0)
		{
			if (node.coefficient_ != 1.0)
				std::cout << " + " << node.coefficient_;
			else
			{
				std::cout << " + ";
				if (node.order_ == 0)
					std::cout << node.coefficient_;
			}
		}
		if (node.coefficient_ < 0)
		{
			if (node.coefficient_ != -1.0)
				std::cout << " - " << -node.coefficient_;
			else
			{
				std::cout << " - ";
				if (node.order_ == 0)
					std::cout << -node.coefficient_;
			}
		}
	}
	if (node.order_ == 0)
		return;
	cout << this->variableName_;
	if (node.order_ != 1)
		std::cout << "^" << node.order_;
}

void MonadicPolynomial::Print(bool flag)
{
	bool first = true;
	for (MonadicPolynomialNode *ptr = this->monadicPolynomail_; ptr != 0;)
	{
		if (first)
		{
			first = false;
			this->PrintNode(*ptr, true);
		}
		else
			this->PrintNode(*ptr);

		ptr = ptr->next_;
	}
	if (flag)
		std::cout << endl;
}

inline bool MonadicPolynomialNode::operator<(const MonadicPolynomialNode &second)
{
	int rel = this->Compare(*this, second);
	if (rel == -1)
		return true;
	else
		return false;
}

inline bool MonadicPolynomialNode::operator>(const MonadicPolynomialNode &second)
{
	int rel = this->Compare(*this, second);
	if (rel == 1)
		return true;
	else
		return false;
}

inline bool MonadicPolynomialNode::operator==(const MonadicPolynomialNode &second)
{
	int rel = this->Compare(*this, second);
	if (rel == 0)
		return true;
	else
		return false;
}


int MonadicPolynomialNode::Compare(const MonadicPolynomialNode &first, const MonadicPolynomialNode &second)
{
	if (first.order_ > second.order_)
		return 1;
	if (first.order_ < second.order_)
		return -1;
	if (first.order_ == second.order_)
		return 0;
}

//######################### BivariatePolynomial #####################//


inline bool BivariatePolynomialNode::operator<(const BivariatePolynomialNode &second)
{
	int rel = this->Compare(*this, second);
	if (rel == -1)
		return true;
	else
		return false;
}

inline bool BivariatePolynomialNode::operator>(const BivariatePolynomialNode &second)
{
	int rel = this->Compare(*this, second);
	if (rel == 1)
		return true;
	else
		return false;
}

inline bool BivariatePolynomialNode::operator==(const BivariatePolynomialNode &second)
{
	int rel = this->Compare(*this, second);
	if (rel == 0)
		return true;
	else
		return false;
}

int BivariatePolynomialNode::Compare(const BivariatePolynomialNode &first, const BivariatePolynomialNode &second)
{
	if (first.order_ > second.order_)
		return 1;
	if (first.order_ < second.order_)
		return -1;
	if (first.order_ == second.order_)
		return 0;
}