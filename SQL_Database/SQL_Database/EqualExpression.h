#pragma once
#include "BinaryOperatorExpression.h"

class EqualExpression : public BinaryOperatorExpression
{
public:
	EqualExpression(MyString&& left, MyString&& right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;
};

