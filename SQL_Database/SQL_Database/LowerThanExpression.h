#pragma once
#include "BinaryOperatorExpression.h"

class LowerThanExpression : public BinaryOperatorExpression
{
public:
	LowerThanExpression(MyString&& left, MyString&& right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;

};

