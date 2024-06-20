#pragma once
#include "Expression.h"

class ConjunctionExpression : public Expression
{
public:
	ConjunctionExpression(Expression* left, Expression* right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;
	~ConjunctionExpression();

private:
	Expression* left;
	Expression* right;
};

