#pragma once
#include "BinaryOperatorExpression.h"

class GreaterThanExpression : public BinaryOperatorExpression
{
public:
	GreaterThanExpression(MyString&& left, MyString&& right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;
};

