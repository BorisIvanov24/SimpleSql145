#include "DisjunctionExpression.h"

DisjunctionExpression::DisjunctionExpression(Expression* left, Expression* right) : left(left), right(right)
{
}

bool DisjunctionExpression::evaluate(const Table& table, unsigned rowIndex) const
{
	return (left->evaluate(table, rowIndex) || right->evaluate(table, rowIndex));
}

DisjunctionExpression::~DisjunctionExpression()
{
	delete left;
	delete right;
}