#include "DisjunctionExpression.h"

DisjunctionExpression::DisjunctionExpression(Expression* left, Expression* right) :
											 BinaryLogicalExpression(left, right)
{
}

bool DisjunctionExpression::evaluate(const Table& table, unsigned rowIndex) const
{
	return (left->evaluate(table, rowIndex) || right->evaluate(table, rowIndex));
}
