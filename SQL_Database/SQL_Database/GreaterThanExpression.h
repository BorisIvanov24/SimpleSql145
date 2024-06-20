#pragma once
#include "Expression.h"

class GreaterThanExpression : public Expression
{
public:
	GreaterThanExpression(MyString&& left, MyString&& right);
	bool evaluate(const Table& table, unsigned rowIndex) const override;

private:
	MyString left; //this is a name of a column
	MyString right;
};

