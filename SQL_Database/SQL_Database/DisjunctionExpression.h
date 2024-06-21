#pragma once
#include "BinaryLogicalExpression.h"

class DisjunctionExpression : public BinaryLogicalExpression
{
public:
	DisjunctionExpression(Expression* left, Expression* right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;
};

