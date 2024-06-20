#include "ConjunctionExpression.h"

ConjunctionExpression::ConjunctionExpression(Expression* left, Expression* right) : left(left), right(right)
{
}

bool ConjunctionExpression::evaluate(const Table& table, unsigned rowIndex) const
{
	return (left->evaluate(table, rowIndex) && right->evaluate(table, rowIndex));
}

ConjunctionExpression::~ConjunctionExpression()
{
	delete left;
	delete right;
}
