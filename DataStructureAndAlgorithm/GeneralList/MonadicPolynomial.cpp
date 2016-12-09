#include <bitset>
#include <algorithm>
#include <iostream>

#include "MonadicPolynomial.h"
#include "MonadicPolynomialNode.h"
using namespace std;


void MonadicPolynomial::Inverse()
{
	MonadicPolynomialNode *ptr = this->monadicPolynomial_;
	while (ptr != 0)
	{
		ptr->coefficient = -ptr->coefficient;
		ptr = ptr->next;
	}
}

void MonadicPolynomial::EraseZeroItem()
{
	MonadicPolynomialNode *ptr1 = this->monadicPolynomial_;
	if (this->monadicPolynomial_ == 0) // no node
		return;
	if (ptr1->next == 0) // just one node
	{
		if (ptr1->coefficient > 0 || ptr1->coefficient < 0);
		else
		{
			ptr1->order = 0;
			return;
		}
	}

	MonadicPolynomialNode *fakeHead = new MonadicPolynomialNode(0, 0);
	fakeHead->next = this->monadicPolynomial_;
	ptr1 = fakeHead;
	MonadicPolynomialNode *ptr2 = this->monadicPolynomial_;
	while (ptr2 != 0)
	{
		if (ptr2->coefficient > 0 || ptr2->coefficient < 0)
		{
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		else
		{
			ptr1->next = ptr2->next;
			MonadicPolynomialNode *temp = ptr2;
			ptr2 = ptr2->next;
			delete temp;
		}
	}
	this->monadicPolynomial_ = fakeHead->next;
	delete fakeHead;
}

void MonadicPolynomial::Insert(const MonadicPolynomialNode &node)
{
	MonadicPolynomialNode *head = this->monadicPolynomial_, *ptr = this->monadicPolynomial_;
	MonadicPolynomialNode *ptrNode = new MonadicPolynomialNode(node.coefficient, node.order);
	if (head == 0)
	{
		this->monadicPolynomial_ = ptrNode;
		return;
	}
	if (ptr->next == 0) // this->monadicPolynomial_ just has one node
	{
		if (node.order > head->order) // new node is greater than former one
		{
			head = ptrNode;
			head->next = this->monadicPolynomial_;
			this->monadicPolynomial_ = head;
			return;
		}
		if (node.order == head->order) // new node is equal with former one
		{
			head->coefficient += node.coefficient;
			if (head->coefficient == 0)
				head->order = 0;
			return;
		}
		if (node.order < head->order)
		{
			head->next = ptrNode;
			return;
		}
			
	}

	while (ptr->next != 0)
	{
		if (node.order > ptr->order)
		{
			ptrNode->next = head;
			head = ptrNode;
			this->monadicPolynomial_ = head;
			return;
		}
		if (node.order == ptr->order)
		{
			ptr->coefficient += node.coefficient;
			return;
		}
		if (node.order < ptr->order && node.order > ptr->next->order)
		{
			ptrNode->next = ptr->next;
			ptr->next = ptrNode;
			return;
		}
		if (node.order == ptr->next->order)
		{
			ptr->next->coefficient += node.coefficient;
			return;
		}
		ptr = ptr->next;
	}
	ptr->next = ptrNode;
}

void MonadicPolynomial::Add(const MonadicPolynomial &another)
{
	MonadicPolynomialNode *ptr = another.monadicPolynomial_;
	while (ptr != 0)
	{
		this->Insert(*ptr);
		ptr = ptr->next;
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
	if (nodes.size() == 0)				//if nodes with no item, then set the header point to 0 and return directly.
	{
		this->monadicPolynomial_ = 0;
		return;
	}
	
	sort(nodes.begin(), nodes.end());			//sort the nodes, the biggest order is at last
	
	MonadicPolynomialNode *ptr = 0;
	bool first = true;
	for (int i = nodes.size() - 1; i >= 0; --i)	//create monadic polynomial with biggest order at head.
	{
		if (nodes[i].coefficient > 0 || nodes[i].coefficient < 0) //if the coefficient of this node is 0, then skip this node
		{
			if (first)	//if i == nodes.size() - 1, then this is first node.
			{
				first = false;
				this->monadicPolynomial_ = new MonadicPolynomialNode(nodes[i].coefficient, nodes[i].order);
				ptr = this->monadicPolynomial_;
			}
			else		//this is not first node
			{
				ptr->next = new MonadicPolynomialNode(nodes[i].coefficient, nodes[i].order);
				ptr = ptr->next;
			}
		}
	}
	ptr->next = 0;		//last node point to 0

	ptr = this->monadicPolynomial_;
	MonadicPolynomialNode *ptr2 = this->monadicPolynomial_->next;
	while (ptr2 != 0)		//this loop will merge items with same order.
	{
		if (*ptr == *ptr2)	//equal means the order of two nodes is equal.
		{
			MonadicPolynomialNode *temp = ptr2;
			ptr->next = temp->next;
			ptr->coefficient += temp->coefficient;	//merge two items
			ptr2 = temp->next;						//ptr2 move a step back, while ptr shouldn't move, because there maybe three or more items have same order
			delete temp;
		}
		else				//if *ptr not equal to *ptr2, then there is no more node equal to *ptr at back, because these nodes are sorted.
		{
			ptr = ptr->next;		//ptr move a step back
			ptr2 = ptr2->next;		//ptr2 move a step back
		}
	}
}

MonadicPolynomial::MonadicPolynomial(const MonadicPolynomial &another)
{
	if (another.monadicPolynomial_ == 0) //if the monadic polynomial is empty, then just return.
	{
		this->monadicPolynomial_ = 0;
		this->variableName_ = another.variableName_;
		return;
	}
	MonadicPolynomialNode *ptr = another.monadicPolynomial_;
	MonadicPolynomialNode *thisPtr = 0, *head = 0;
	head = new MonadicPolynomialNode(ptr->coefficient, ptr->order);
	ptr = ptr->next;
	thisPtr = head;
	while (ptr != 0) //copy all nodes from another in this loop
	{
		thisPtr->next = new MonadicPolynomialNode(ptr->coefficient, ptr->order);
		ptr = ptr->next;
		thisPtr = thisPtr->next;
	}
	this->monadicPolynomial_ = head;
}

MonadicPolynomial::~MonadicPolynomial()
{
	MonadicPolynomialNode *temp, *ptr;
	temp = this->monadicPolynomial_;
	this->monadicPolynomial_ = 0;
	ptr = temp->next;
	while (ptr != 0)
	{
		delete temp;
		temp = ptr;
		ptr = ptr->next;
	}
	delete temp;
}

void MonadicPolynomial::PrintNode(const MonadicPolynomialNode &node, bool first)
{
	if (first)
	{
		if (node.coefficient > 0 && node.coefficient != 1.0)
			std::cout << node.coefficient;
		if (node.coefficient < 0 && node.coefficient != -1.0)
			std::cout << node.coefficient;
		if (node.coefficient == -1.0)
			std::cout << "-";
	}
	else
	{
		if (node.coefficient > 0)
		{
			if (node.coefficient != 1.0)
				std::cout << " + " << node.coefficient;
			else
			{
				std::cout << " + ";
				if (node.order == 0)
					std::cout << node.coefficient;
			}
		}
		if (node.coefficient < 0)
		{
			if (node.coefficient != -1.0)
				std::cout << " - " << -node.coefficient;
			else
			{
				std::cout << " - ";
				if (node.order == 0)
					std::cout << -node.coefficient;
			}
		}
	}
	if (node.order == 0)
		return;
	cout << this->variableName_;
	if (node.order != 1)
		std::cout << "^" << node.order;
}

void MonadicPolynomial::Print(bool flag)
{
	bool first = true;
	for (MonadicPolynomialNode *ptr = this->monadicPolynomial_; ptr != 0;)
	{
		if (first)
		{
			first = false;
			this->PrintNode(*ptr, true);
		}
		else
			this->PrintNode(*ptr);

		ptr = ptr->next;
	}
	if (flag)
		std::cout << endl;
}





