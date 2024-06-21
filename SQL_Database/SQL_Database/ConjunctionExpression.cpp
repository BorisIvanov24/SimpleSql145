#include "ConjunctionExpression.h"

ConjunctionExpression::ConjunctionExpression(Expression* left, Expression* right) : 
											 BinaryLogicalExpression(left, right)
{
}

bool ConjunctionExpression::evaluate(const Table& table, unsigned rowIndex) const
{
	return (left->evaluate(table, rowIndex) && right->evaluate(table, rowIndex));
}

