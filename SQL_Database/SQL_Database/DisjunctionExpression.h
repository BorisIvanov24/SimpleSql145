#pragma once
#include "Expression.h"
class DisjunctionExpression : public Expression
{
public:
	DisjunctionExpression(Expression* left, Expression* right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;
	~DisjunctionExpression();

private:
	Expression* left;
	Expression* right;
};

