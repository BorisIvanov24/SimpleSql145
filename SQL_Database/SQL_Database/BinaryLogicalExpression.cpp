#include "BinaryLogicalExpression.h"

BinaryLogicalExpression::BinaryLogicalExpression(Expression* left, Expression* right) :
	left(left), right(right)
{
}

BinaryLogicalExpression::~BinaryLogicalExpression()
{
	delete left;
	delete right;
}