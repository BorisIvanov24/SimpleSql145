#pragma once
#include "BinaryLogicalExpression.h"

class ConjunctionExpression : public BinaryLogicalExpression
{
public:
	ConjunctionExpression(Expression* left, Expression* right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;

};

