#pragma once
#include "Expression.h"

class BinaryOperatorExpression : public Expression
{
public:
	BinaryOperatorExpression(MyString&& left, MyString&& right);
	bool evaluate(const Table& table, unsigned rowIndex) const = 0;

protected:
	MyString left; //this is a name of a column
	MyString right;
};

