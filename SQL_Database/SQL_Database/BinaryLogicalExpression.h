#pragma once
#include "Expression.h"

class BinaryLogicalExpression : public Expression
{
public:
	BinaryLogicalExpression(Expression* left, Expression* right);
	bool evaluate(const Table& table, unsigned rowIndex) const = 0;
	~BinaryLogicalExpression();

protected:
	Expression* left;
	Expression* right;
};

